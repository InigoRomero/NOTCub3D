/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 19:17:51 by iromero-          #+#    #+#             */
/*   Updated: 2019/12/21 19:31:20 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	calcularobj(t_mapinfo *s)
{
		s->alturalinea = 0;

		while (s->obend - s->obstart < s->h[7])
		{
			s->alturalinea = (int)(s->y / s->objdist);
			s->obstart = -s->alturalinea / 2 + (s->y / 1.3);
			if (s->obstart < 0)
				s->obstart = 0;
			s->obend = s->alturalinea /  2 + (s->y / 1.3);
			if (s->obend >= s->y)
				s->obend = s->y - 1;
		}
}

void	raycasting(t_mapinfo *s)
{
	int n;

	n = 0;
	s->obx = 0;
	s->oby = 0;
	s->img = mlx_new_image(s->mlx_ptr, s->x, s->y);
	s->img_ptr = mlx_get_data_addr(s->img, &s->bpp, &s->sl, &s->endian);
	s->wlone[7] = mlx_xpm_file_to_image(s->mlx_ptr, "src/obj.xpm", &s->w[7], &s->h[7]);
	s->wdata[7] = mlx_get_data_addr(s->wlone[7], &s->wbpp[7], &s->wsl[7], &s->wendian[7]);
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
		if (s->mapn[(int)s->posX][(int)s->posY] == 2)
		{
			s->mapn[(int)s->posX][(int)s->posY] = 0;
			s->score += 100;
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
			if (s->mapn[s->mapX][s->mapY] == 2)
			{
				s->obj = 1;
				s->objposy = s->mapY;
				s->objposx = s->mapX;
				if (s->side == 0)
					s->objdist = (s->objposx - s->posX + (1 - s->stepX) / 2) / s->rayDirX;
				else
					s->objdist = (s->objposy - s->posY + (1 - s->stepY) / 2) / s->rayDirY;
			}
			if (s->mapn[s->mapX][s->mapY] == 1)
				s->hit = 1;
		}
		if (s->side == 0)
			s->perpWallDist = (s->mapX - s->posX + (1 - s->stepX) / 2) / s->rayDirX;
		else
			s->perpWallDist = (s->mapY - s->posY + (1 - s->stepY) / 2) / s->rayDirY;
		s->lineHeight = (int)(s->y / s->perpWallDist);
		s->drawStart = -s->lineHeight / 2 + s->y / 2;
		if (s->drawStart < 0)
			s->drawStart = 0;
		s->drawEnd = s->lineHeight / 2 + s->y / 2;
		if (s->drawEnd >= s->y)
			s->drawEnd = s->y - 1;
		if (s->obj == 1)
		calcularobj(s);
		ft_verLine(n, s->drawStart, s->drawEnd, s->color, s);
		n++;
			s->obj = 0;
	}
	s->count = 0;
	//ft_gun(s);
	mlx_put_image_to_window(s->mlx_ptr, s->win_ptr,  s->img, 0, 0 );
	mlx_put_image_to_window(s->mlx_ptr, s->win_ptr,  s->wlone[5], s->fpposx, s->fpposy);
	if (s->obj == 1)
		mlx_put_image_to_window(s->mlx_ptr, s->win_ptr,  s->wlone[7], s->obstart, s->obend );
	mlx_string_put ( s->mlx_ptr, s->win_ptr, 20, 20, 293994,  ft_itoa(s->score));
	mlx_destroy_image(s->mlx_ptr, s->wlone[7]);
	mlx_destroy_image(s->mlx_ptr, s->img);
	s->obj = 0;
}