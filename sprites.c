#include "ft_cub3d.h"

// SPRITE
void	get_sprite(t_s *s)
{
	int r;
	int c;
	int i;

	r = -1;
	i = 0;
	s->sprite_pos_x = malloc(sizeof(int *) * s->count_sprite);
	s->sprite_pos_y = malloc(sizeof(int *) * s->count_sprite);
	if (!s->sprite_pos_x || !s->sprite_pos_y)
		return ;
	while (++r < s->max_row)
	{
		c = -1;
		while (++c < s->max_col)
		{
			if (s->mapi[r][c] == 2)
			{
				s->sprite_pos_x[i] = r + 0.5;
				s->sprite_pos_y[i++] = c + 0.5;
			}
		}
	}
}

void	swap(t_s *s, int i, int j)
{
	double	tmp;

	s->s_distance = ((s->pos_x - s->sprite_pos_x[j]) * (s->pos_x - s->sprite_pos_x[j]) + (s->pos_y - s->sprite_pos_y[j]) * (s->pos_y - s->sprite_pos_y[j]));
	tmp = s->sprite_pos_x[i];
	s->sprite_pos_x[i] =  s->sprite_pos_x[i + 1];
	s->sprite_pos_x[i + 1] = tmp;
	tmp = s->sprite_pos_y[i];
	s->sprite_pos_y[i] =  s->sprite_pos_y[i + 1];
	s->sprite_pos_y[i + 1] = tmp;
}


void	sorting(t_s *s)
{
	int i;
	int j;

	i = 0;
	while (i < s->count_sprite - 1)
	{
		s->s_distance = ((s->pos_x - s->sprite_pos_x[i]) * (s->pos_x - s->sprite_pos_x[i]) + (s->pos_y - s->sprite_pos_y[i]) * (s->pos_y - s->sprite_pos_y[i]));
		j = i + 1;
		while (j < s->count_sprite)
		{
			if (((s->pos_x - s->sprite_pos_x[j]) * (s->pos_x - s->sprite_pos_x[j]) + (s->pos_y - s->sprite_pos_y[j]) * (s->pos_y - s->sprite_pos_y[j])) > s->s_distance)
				swap(s, i, j);
			j++;
		}
		i++;
	}
}

void		print_sprites(t_s *s)
{
	int		y;
	int		d;
	char	*dst;

	d = 0;
	y = s->drawstart_y;
	
	//printf("tex_y:%d color:%d\n", s->tex_y, s->color);
	//printf("dra_star_x:%d dra_end_x:%d dra_star_y:%d dra_end_y:%d \n", s->drawstart_x, s->drawend_x, s->drawstart_y, s->drawend_y);
	while (y < s->drawend_y)
	{
		d = (y) * 256 - s->h * 128 + s->sprite_h * 128;
		s->tex_y = ((d * s->hxpm[4]) / s->sprite_h) / 256;
		s->color = s->xpmdata_s[(s->xpmsize[4] / 4) * s->tex_y + s->tex_x];
		if ((s->color & BLACK) != 0)
			s->addr[y * s->w + s->stripe] = s->color;
		if (s->color != 0)
		{
			dst = s->addr + (y * s->size + s->stripe * (s->bits / 8));
			*(unsigned int *)dst = s->color;
		}
		y++;
	}
}

void	sprites(t_s *s)
{
	int i = 0;
	sorting(s);
	//printf("dra_star_x:%d dra_end_x:%d dra_star_y:%d dra_end_y:%d \n", s->drawstart_x, s->drawend_x, s->drawstart_y, s->drawend_y);
	while (i < s->count_sprite)
	{
		s->sprite_x = s->sprite_pos_x[i] - s->pos_x;
		s->sprite_y = s->sprite_pos_y[i] - s->pos_y;
		s->invdet = 1.0 / (s->plane_x * s->dir_y - s->dir_x * s->plane_y);
		s->transform_x = s->invdet * (s->dir_y * s->sprite_x - s->dir_x * s->sprite_y);
		s->transform_y = s->invdet * (-s->plane_y * s->sprite_x + s->plane_x * s->sprite_y);
		s->sprite_screen_x = (int)((s->w / 2) * (1 + s->transform_x / s->transform_y));
		s->sprite_h = abs((int)(s->h / s->transform_y));
		s->drawstart_y = (-s->sprite_h / 2) + (s->h / 2);
		if (s->drawstart_y < 0)
			s->drawstart_y = 0;
		s->drawend_y = (s->sprite_h / 2) + (s->h / 2);
		if (s->drawend_y >= s->h)
			s->drawend_y = s->h - 1;
		s->sprite_w = abs((int)(s->h / s->transform_y));
		s->drawstart_x = (-s->sprite_w / 2) + s->sprite_screen_x;
		if (s->drawstart_x < 0)
			s->drawstart_x = 0;
		s->drawend_x = (s->sprite_w / 2) + s->sprite_screen_x;
		if (s->drawend_x >= s->w)
			s->drawend_x = s->w - 1;
		i++;
	}
	s->stripe = s->drawstart_x;
	while (s->stripe < s->drawend_x)
	{
		s->tex_x = (int)((256 * (s->stripe - ((-s->sprite_w / 2) + s->sprite_screen_x))) * s->wxpm[4] / s->sprite_w) / 256;
		if (s->transform_y > 0 && s->stripe > 0 && s->stripe < s->w && s->transform_y < s->s_buff[s->stripe])
			print_sprites(s);
		s->stripe++;
	}
}


//FIN SPRITE
