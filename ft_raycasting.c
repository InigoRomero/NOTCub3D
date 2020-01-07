/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 19:17:51 by iromero-          #+#    #+#             */
/*   Updated: 2020/01/06 19:14:11 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	raycaauxfour(t_mapinfo *s)
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
	if (s->obj == 1)
		calcularobj(s);
	ft_verline(s);
	s->cox++;
	s->obj = 0;
}

void	raycaauxthre(t_mapinfo *s)
{
	if (s->mapn[s->mapx][s->mapy] == 2)
	{
		if (s->objbool == 0)
		{
			s->objposx = s->cox;
			s->objbool = 1;
		}
		s->obj = 1;
		s->hp = s->hp - 0.0006;
		s->objposy = s->mapy;
		s->objposxtwo = s->mapx;
		if (s->side == 0)
			s->objdist = (s->objposxtwo - s->posx +
				(1 - s->stepx) / 2) / s->raydirx;
		else
			s->objdist = (s->objposy - s->posy +
				(1 - s->stepy) / 2) / s->raydiry;
	}
	if (s->mapn[s->mapx][s->mapy] == 1)
		s->hit = 1;
}

void	raycaauxtwo(t_mapinfo *s)
{
	if (s->mapn[(int)s->posx][(int)s->posy] == 2)
	{
		s->mapn[(int)s->posx][(int)s->posy] = 0;
		s->score += 100;
		s->hp += 3;
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

void	raycaaux(t_mapinfo *s)
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

void	raycasting(t_mapinfo *s)
{
	s->cox = 0;
	s->obx = 0;
	s->objbool = 0;
	s->img = mlx_new_image(s->mlx_ptr, s->x, s->y);
	s->img_ptr = mlx_get_data_addr(s->img, &s->bpp, &s->sl, &s->endian);
	s->wlone[7] = mlx_xpm_file_to_image(s->mlx_ptr,
		"src/obj.xpm", &s->w[7], &s->h[7]);
	s->wdata[7] = mlx_get_data_addr(s->wlone[7],
		&s->wbpp[7], &s->wsl[7], &s->wendian[7]);
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
	}
	to_img(s);
}
