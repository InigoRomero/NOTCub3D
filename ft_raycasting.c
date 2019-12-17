/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 19:17:51 by iromero-          #+#    #+#             */
/*   Updated: 2019/12/17 20:03:36 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	raycasting(t_mapinfo *s)
{
	int n;

	n = 0;
	s->img = mlx_new_image(s->mlx_ptr, s->x, s->y);
	s->img_ptr = mlx_get_data_addr(s->img, &s->bpp, &s->sl, &s->endian);
	ft_sky(s);
	while (n < s->x)
	{
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
			if (s->mapn[s->mapX][s->mapY] == 1)
				s->hit = 1;
		}
		if (s->side == 0)
			s->perpWallDist = (s->mapX - s->posX + (1 - s->stepX) / 2) / s->rayDirX;
		else
			s->perpWallDist = (s->mapY - s->posY + (1 - s->stepY) / 2) / s->rayDirY;
		s->lineHeight = (int)(s->y / s->perpWallDist);
		s->drawStart = -s->lineHeight / 2 + s->y  / 2;
		if (s->drawStart < 0)
			s->drawStart = 0;
		s->drawEnd = s->lineHeight / 2 + s->y  / 2;
		if (s->drawEnd >= s->y)
			s->drawEnd = s->y - 1;
		if (s->mapn[s->mapX][s->mapY] == 1)
			s->id = 0;
		if (s->side == 1)
			s->id = 2;
		ft_verLine(n, s->drawStart, s->drawEnd, s->color, s);
		n++;
	}
	//fp(s);
	ft_gun(s);
	mlx_put_image_to_window(s->mlx_ptr, s->win_ptr,  s->img, 0, 0 );
	//mlx_put_image_to_window(s->mlx_ptr, s->win_ptr,  s->img_psr, s->x / 3, s->y - s->y / 3);
	mlx_destroy_image(s->mlx_ptr, s->img);
	//mlx_destroy_image(s->mlx_ptr, s->img_psr);
}