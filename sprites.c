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
	s->s_distance = malloc(sizeof(int *) * s->count_sprite);
	if (!s->sprite_pos_x || !s->sprite_pos_y || !s->s_distance)
		return ;
	while (++r < noflines(s))
	{
		c = -1;
		while (++c < noffiles(s))
		{
			if (s->mapn[r][c] >= 2)
			{
				s->sprite_pos_x[i] = r + 0.5;
				s->sprite_pos_y[i++] = c + 0.5;
			}
		}
	}
}

void	swap(t_s *s, int i)
{
	double	tmp;

	tmp = s->sprite_pos_x[i];
	s->sprite_pos_x[i] =  s->sprite_pos_x[i + 1];
	s->sprite_pos_x[i + 1] = tmp;
	tmp = s->sprite_pos_y[i];
	s->sprite_pos_y[i] =  s->sprite_pos_y[i + 1];
	s->sprite_pos_y[i + 1] = tmp;
	tmp = s->s_distance[i];
	s->s_distance[i] =  s->s_distance[i + 1];
	s->s_distance[i + 1] = tmp;
}

void calculate_distance(t_s *s)
{
	int i;

	i = -1;
	while (++i < s->count_sprite)
		s->s_distance[i] = ((s->posx - s->sprite_pos_x[i]) * (s->posx - s->sprite_pos_x[i]) + (s->posy - s->sprite_pos_y[i]) * (s->posy - s->sprite_pos_y[i]));

}

void	sorting(t_s *s)
{
	int i;
	int j;

	i = 0;

	calculate_distance(s);
	while (i < s->count_sprite)
	{
		j = -1;
		while (++j < s->count_sprite - i - 1)
			if (s->s_distance[j] < s->s_distance[j + 1])
				swap(s, j);
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
		d = (y) * (s->h[s->id] * 4) - s->y * (s->h[s->id] * 2) + s->sprite_h * (s->h[s->id] * 2);
		s->tex_y = ((d * s->h[s->id]) / s->sprite_h) / (s->h[s->id] * 4);
		s->color = s->data_spr[s->id][(s->wsl[s->id] / 4) * s->tex_y + s->tex_x];
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
        if (s->mapn[(int)s->sprite_pos_x[i]][(int)s->sprite_pos_y[i]] >= 2 )
        {
            if (s->mapn[(int)s->sprite_pos_x[i]][(int)s->sprite_pos_y[i]] == 2)
                s->id = 7;
            if (s->mapn[(int)s->sprite_pos_x[i]][(int)s->sprite_pos_y[i]] == 3)
                s->id = 8;
			if (s->mapn[(int)s->sprite_pos_x[i]][(int)s->sprite_pos_y[i]] == 4)
            {
				s->id = 9;
				if ((int)s->sprite_pos_x[i] % 2 != 0)
					s->id = 10;
				if ((int)s->sprite_pos_y[i] % 3 != 0)
					s->id = 11;
			}
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
                if (s->transform_y > 0 && s->stripe > 0 && s->stripe < s->x && s->transform_y < s->s_buff[s->stripe])
				{
					if (s->id >= 9 && s->score < s->coin_counter * 100)
						s->hp -= 0.00099;
                	s->tex_x = (int)(((s->h[s->id] * 4) * (s->stripe - ((-s->sprite_w / 2) + s->sprite_screen_x))) * s->w[s->id] / s->sprite_w) / (s->h[s->id] * 4);
                    print_sprites(s);
				}
                s->stripe++;
            }
        }
        i++;
	}
}
