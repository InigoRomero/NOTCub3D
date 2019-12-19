/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 19:17:51 by iromero-          #+#    #+#             */
/*   Updated: 2019/12/19 21:37:54 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	calcularobj(t_mapinfo *s)
{
		s->obstart =   s->drawEnd - s->w[7];
		if (s->obstart < 0)
			s->obstart = 0;
		s->obend = s->y;
		if (s->obend >= s->y)
			s->obend = s->drawEnd  + s->w[7];
}

void	raycasting(t_mapinfo *s)
{
	int n;

	n = 0;
	s->img = mlx_new_image(s->mlx_ptr, s->x, s->y);
	s->img_ptr = mlx_get_data_addr(s->img, &s->bpp, &s->sl, &s->endian);
	while (n < s->x)
	{
		s->obj = 0;
		s->cameraX = 2 * n / (double)s->x - 1;
		s->rayDirX = s->dirX + s->planeX * s->cameraX;
		s->rayDirY = s->dirY + s->planeY * s->cameraX;
		s->mapX = (int)s->posX;
		s->mapY = (int)s->posY;
		s->deltaDistX = fabs((1 / s->rayDirX));
		s->deltaDistY = fabs((1 / s->rayDirY));
		s->hit = 0;
		if (s->rayDirX < 0)
		{
			s->stepX = -1;
			s->sideDistX = (s->posX - s->mapX) * s->deltaDistX;
		}
		else
		{
			s->stepX = 1;
			s->sideDistX = (s->mapX + 1.0 - s->posX) * s->deltaDistX;
		}
		if (s->rayDirY < 0)
		{
			s->stepY = -1;
			s->sideDistY = (s->posY - s->mapY) * s->deltaDistY;
		}
		else
		{
			s->stepY = 1;
			s->sideDistY = (s->mapY + 1.0 - s->posY) * s->deltaDistY;
		}
		while (s->hit == 0)
		{
			if (s->sideDistX < s->sideDistY)
			{
				s->sideDistX += s->deltaDistX;
				s->mapX += s->stepX;
				s->side = 0;
			}
			else
			{
				s->sideDistY += s->deltaDistY;
				s->mapY += s->stepY;
				s->side = 1;
			}
			if (s->mapn[s->mapX][s->mapY] == -1)
			{
				s->obj = 1;
				s->objposy = s->mapY;
				s->objposx = s->mapX;
			}
			if (s->mapn[s->mapX][s->mapY] == 1)
				s->hit = 1;
		}
		if (s->side == 0)
			s->perpWallDist = (s->mapX - s->posX + (1 - s->stepX) / 2) / s->rayDirX;
		else
			s->perpWallDist = (s->mapY - s->posY + (1 - s->stepY) / 2) / s->rayDirY;
		s->lineHeight = (int)(s->x / s->perpWallDist);
		 //calculate lowest and highest pixel to fill in current stripe
		s->drawStart = -s->lineHeight / 2 + s->y  / 2;
		if (s->drawStart < 0)
			s->drawStart = 0;
		s->drawEnd = s->lineHeight / 2 + s->y  / 2;
		if (s->drawEnd >= s->y)
			s->drawEnd = s->y - 1;
		if (s->obj == 1)
			calcularobj(s);
		ft_verLine(n, s->drawStart, s->drawEnd, s->color, s);
		n++;
	}
	s->count = 0;
	//ft_gun(s);
	mlx_put_image_to_window(s->mlx_ptr, s->win_ptr,  s->img, 0, 0 );
	mlx_put_image_to_window(s->mlx_ptr, s->win_ptr,  s->wlone[5], s->fpposx, s->fpposy );
	//mlx_put_image_to_window(s->mlx_ptr, s->win_ptr,  s->img_psr, s->x / 3, s->y - s->y / 3);
	mlx_destroy_image(s->mlx_ptr, s->img);
	//mlx_destroy_image(s->mlx_ptr, s->img_psr);
}