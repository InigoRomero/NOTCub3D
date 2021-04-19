#include "ft_cub3d.h"

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
	while (++r < noflines(s))
	{
		c = -1;
		while (++c < noffiles(s))
		{
			if (s->mapn[r][c] == 2 || s->mapn[r][c] == 3 | s->mapn[r][c] == 4)
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

	s->s_distance = ((s->posx - s->sprite_pos_x[j]) * (s->posx - s->sprite_pos_x[j]) + (s->posy - s->sprite_pos_y[j]) * (s->posy - s->sprite_pos_y[j]));
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
		s->s_distance = ((s->posx - s->sprite_pos_x[i]) * (s->posx - s->sprite_pos_x[i]) + (s->posy - s->sprite_pos_y[i]) * (s->posy - s->sprite_pos_y[i]));
		j = i + 1;
		while (j < s->count_sprite)
		{
			if (((s->posx - s->sprite_pos_x[j]) * (s->posx - s->sprite_pos_x[j]) + (s->posy - s->sprite_pos_y[j]) * (s->posy - s->sprite_pos_y[j])) > s->s_distance)
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
	
    while (y < s->drawend_y)
	{
		d = (y) * (s->h[7] * 4) - s->y * (s->h[7] * 2) + s->sprite_h * (s->h[7] * 2);
		s->tex_y = ((d * s->h[4]) / s->sprite_h) / (s->h[7] * 4);
		s->color = s->data_spr[s->id][(s->wsl[4] / 4) * s->tex_y + s->tex_x];
		if ((s->color & BLACK) != 0)
			s->img_ptr[y * s->x + s->stripe] = s->color;
		if (s->color != 0)
		{
			dst = s->img_ptr + (y * s->sl + s->stripe * (s->bpp / 8));
			*(unsigned int *)dst = s->color;
		}
		y++;
	}
}

void	sprites(t_s *s)
{
	int i = 0;
	sorting(s);
	while (i < s->count_sprite)
	{
        if (s->mapn[(int)s->sprite_pos_x[i]][(int)s->sprite_pos_y[i]] == 2 || s->mapn[(int)s->sprite_pos_x[i]][(int)s->sprite_pos_y[i]] == 3 )
        {
            if (s->mapn[(int)s->sprite_pos_x[i]][(int)s->sprite_pos_y[i]] == 2)
                s->id = 0;
            if (s->mapn[(int)s->sprite_pos_x[i]][(int)s->sprite_pos_y[i]] == 3)
                s->id = 1;
            s->sprite_x = s->sprite_pos_x[i] - s->posx;
            s->sprite_y = s->sprite_pos_y[i] - s->posy;
            s->invdet = 1.0 / (s->planex * s->diry - s->dirx * s->planey);
            s->transform_x = s->invdet * (s->diry * s->sprite_x - s->dirx * s->sprite_y);
            s->transform_y = s->invdet * (-s->planey * s->sprite_x + s->planex * s->sprite_y);
            s->sprite_screen_x = (int)((s->x / 2) * (1 + s->transform_x / s->transform_y));
            s->sprite_h = abs((int)(s->y / s->transform_y));
            s->drawstart_y = (-s->sprite_h / 2) + (s->y / 2);
            if (s->drawstart_y < 0)
                s->drawstart_y = 0;
            s->drawend_y = (s->sprite_h / 2) + (s->y / 2);
            if (s->drawend_y >= s->y)
                s->drawend_y = s->y - 1;
            s->sprite_w = abs((int)(s->y / s->transform_y));
            s->drawstart_x = (-s->sprite_w / 2) + s->sprite_screen_x;
            if (s->drawstart_x < 0)
                s->drawstart_x = 0;
            s->drawend_x = (s->sprite_w / 2) + s->sprite_screen_x;
            if (s->drawend_x >= s->x)
                s->drawend_x = s->x - 1;
            s->stripe = s->drawstart_x;
            while (s->stripe < s->drawend_x)
            {
                s->tex_x = (int)(((s->h[7] * 4) * (s->stripe - ((-s->sprite_w / 2) + s->sprite_screen_x))) * s->w[4] / s->sprite_w) / (s->h[7] * 4);
                if (s->transform_y > 0 && s->stripe > 0 && s->stripe < s->x && s->transform_y < s->s_buff[s->stripe])
                    print_sprites(s);
                s->stripe++;
            }
        }
        i++;
	}
}