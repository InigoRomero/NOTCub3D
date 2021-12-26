/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 19:17:51 by iromero-          #+#    #+#             */
/*   Updated: 2021/12/22 18:21:23 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void create_snow(t_s *s)
{
	int x = 0, y;

	while (x < s->x)
	{
		y = 0;
		while (y < s->snow_height) 
		{
			if (y < s->drawstart)
				s->snow[x][y] = 0;
			int r = rand() % 300;
			if (r == 1)
			{
				s->snow[x][y] = 1;
				s->snow[x][y + 1] = 1;
				s->snow[x + 1][y] = 1;
				s->snow[x + 1][y + 1] = 1;
			}
			y += 2;
		}
		x+=2;
	}
	s->snow_height = 0;
}

static void	draw_snow(t_s *s)
{
	int i = -1, h = s->y * 3, color = WHITE, color2 = 0;
	
	while (++i < h) {
		if (s->snow[s->cox][i -
		 s->snow_height] == 1)
			ft_memcpy(s->img_ptr + 4 * s->x * i + s->cox * 4, &color, sizeof(int));
	}
}

static void	set_floor(t_s *s)
{
	if (s->side == 0 && s->raydirx > 0)
	{
		s->x_floor = s->mapx;
		s->y_floor = s->mapy + s->x_wall;
	}
	else if (s->side == 0 && s->raydirx < 0)
	{
		s->x_floor = s->mapx + 1.0;
		s->y_floor = s->mapy + s->x_wall;
	}
	else if (s->side == 1 && s->raydiry > 0)
	{
		s->x_floor = s->mapx + s->x_wall;
		s->y_floor = s->mapy;
	}
	else
	{
		s->x_floor = s->mapx + s->x_wall;
		s->y_floor = s->mapy + 1.0;
	}
}

void		draw_floor(t_s *s, int x, int start, int end)
{
	set_floor(s);
	start += 100;
	while (++start < end)
	{
		s->curdist = s->y / (2.0 * start - s->y);
		s->weight = s->curdist / s->perpwalldist;
		s->x_curfloortext = s->weight * s->x_floor + (1.0 - s->weight) *
			s->posy;
		s->y_curfloortext = s->weight * s->y_floor + (1.0 - s->weight) *
			s->posx;
		s->x_floortext = (int)(s->x_curfloortext * s->w[s->id]) %
			s->w[s->id];
		s->y_floortext = (int)(s->y_curfloortext * s->h[s->id]) %
			s->h[s->id];
	/*	ft_memcpy(s->img_ptr + 4 * s->x * start + 4 * x,
			&s->wdata[s->id][4 * s->w[s->id] * s->x_floortext +
			4 * s->y_floortext], sizeof(int));*/
		if ((int)s->wdata[6][4 * s->w[6] * s->x_floortext +
			(s->wbpp[6] / 8) * s->y_floortext]) {
				ft_memcpy(s->img_ptr + (s->wbpp[6] / 8) * s->x * start
					+ start * (s->wbpp[6] / 8),
						&s->wdata[6][s->y_floortext % s->h[6] * s->wsl[6] +
						s->x_floortext % s->w[6] * s->wbpp[6] / 8], sizeof(int));
			}
	}
}

void	raycaauxfour(t_s *s)
{
	if (s->side == 0)
		s->perpwalldist = (s->mapx - s->posx +
		(1 - s->stepx) / 2) / s->raydirx;
	else
		s->perpwalldist = (s->mapy - s->posy +
			(1 - s->stepy) / 2) / s->raydiry;
	s->lineheight = (int)(s->y / s->perpwalldist);
	s->drawstart = -s->lineheight / 2 + s->y / 2;
	if (s->drawstart < 0)
		s->drawstart = 0;
	s->drawend = s->lineheight / 2 + s->y / 2;
	if (s->drawend >= s->y)
		s->drawend = s->y - 1;
	ft_verline(s);
	if (s->count_sprite > 0)
		s->s_buff[s->cox] = s->perpwalldist;
}

void	raycaauxthre(t_s *s)
{
	if (s->mapn[s->mapx][s->mapy] == 1)
		s->hit = 1;
}

void	raycaauxtwo(t_s *s)
{
	if (s->mapn[(int)s->posx][(int)s->posy] == 2)
	{
		s->mapn[(int)s->posx][(int)s->posy] = 0;
		s->score += 100;
		s->coin_counter--;
	/*	if (s->hp + 3 > 200)
			s->hp = 200;
		else
			s->hp += 3;*/
	}
	while (s->hit == 0)
	{
		if (s->sidedistx < s->sidedisty)
		{
			s->sidedistx += s->deltadistx;
			s->mapx += s->stepx;
			s->side = 0;
		}
		else
		{
			s->sidedisty += s->deltadisty;
			s->mapy += s->stepy;
			s->side = 1;
		}
		raycaauxthre(s);
	}
	raycaauxfour(s);
}

void	raycaaux(t_s *s)
{
	if (s->raydirx < 0)
	{
		s->stepx = -1;
		s->sidedistx = (s->posx - s->mapx) * s->deltadistx;
	}
	else
	{
		s->stepx = 1;
		s->sidedistx = (s->mapx + 1.0 - s->posx) * s->deltadistx;
	}
	if (s->raydiry < 0)
	{
		s->stepy = -1;
		s->sidedisty = (s->posy - s->mapy) * s->deltadisty;
	}
	else
	{
		s->stepy = 1;
		s->sidedisty = (s->mapy + 1.0 - s->posy) * s->deltadisty;
	}
	raycaauxtwo(s);
}

void	raycasting(t_s *s)
{
	s->cox = 0;
	s->obx = 0;

	s->s_buff = malloc(sizeof(int) * s->x);
	/*if (s->hp <= 0)
	{
		write(1, "GAME OVER LOSER TRUPER", 23);
		exit(1);
	}*/
	while (s->cox < s->x)
	{
		s->camerax = 2 * s->cox / (double)s->x - 1;
		s->raydirx = s->dirx + s->planex * s->camerax;
		s->raydiry = s->diry + s->planey * s->camerax;
		s->mapx = (int)s->posx;
		s->mapy = (int)s->posy;
		s->deltadistx = fabs((1 / s->raydirx));
		s->deltadisty = fabs((1 / s->raydiry));
		s->hit = 0;
		raycaaux(s);
		draw_snow(s);
		s->cox++;
		//	draw_floor(s, s->cox, s->drawend - 1, s->y);
	}
	s->snow_height ++;
	if (s->snow_height >= s->y)
		create_snow(s);
	if (s->count_sprite > 0)
		sprites(s);
	to_img(s);
}
