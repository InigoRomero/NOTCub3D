/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 19:38:44 by iromero-          #+#    #+#             */
/*   Updated: 2019/12/21 20:04:31 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	put_pxl_to_img(t_mapinfo *s, int x, int y)
{
	int n;

	if (x < s->x && y < s->y)
	{
		n = abs((((y * (s->h[s->id] * 4) - s->y * (s->h[s->id] * 2)
			+ s->lineHeight * (s->h[s->id] * 2)) * s->h[s->id])
					/ s->lineHeight) / (s->h[s->id] * 4));
		ft_memcpy(s->img_ptr + (s->wbpp[s->id] / 8) * s->x * y
			+ x * (s->wbpp[s->id] / 8),
				&s->wdata[s->id][n % s->h[s->id] * s->wsl[s->id] +
				s->x_text % s->w[s->id] * s->wbpp[s->id] / 8], sizeof(int));
	}
}

void	auxlinetwo(t_mapinfo *s)
{
	while (s->j < s->obend && s->j - s->obstart <
		s->h[7] && s->count < s->w[7])
	{
		if (s->wdata[7][s->oby % s->h[7] * s->wsl[7] +
		s->obx % s->w[7] * s->wbpp[7] / 8] != 0)
			ft_memcpy(s->img_ptr + (s->wbpp[7] / 8) *
				s->x * s->j + s->cox * (s->wbpp[7] / 8),
			&s->wdata[7][s->oby % s->h[7] * s->wsl[7] +
			s->obx % s->w[7] * s->wbpp[7] / 8], sizeof(int));
		s->oby++;
		s->j++;
	}
	s->obx++;
}

void	auxline(t_mapinfo *s)
{
	if (s->side == 1 && s->rayDirY < 0)
		s->id = 0;
	s->x_text = (int)(s->x_wall * (double)s->w[s->id]);
	s->x_text = abs(s->x_text);
	while (s->j <= s->drawEnd)
		put_pxl_to_img(s, s->cox, s->j++);
	while (s->j < s->y)
	{
		ft_memcpy(s->img_ptr + 4 * s->x * s->j +
			s->cox * 4, &s->color2, sizeof(int));
		s->j++;
	}
	if (s->obj == 1)
	{
		s->id = 7;
		s->count++;
		s->j = s->obstart;
		if (s->side == 0)
			s->x_wall = s->posY + s->perpWallDist * s->rayDirY;
		else
			s->x_wall = s->posX + s->perpWallDist * s->rayDirX;
		s->x_text = (int)(s->x_wall * (double)s->w[s->id]);
		s->x_text = abs(s->x_text);
		auxlinetwo(s);
	}
}

void	ft_verline(t_mapinfo *s)
{
	s->color2 = 293994;
	s->j = 0;
	while (s->j < s->drawStart)
	{
		ft_memcpy(s->img_ptr + (s->wbpp[1] / 8) * s->x *
			s->j + s->cox * (s->wbpp[1] / 8),
			&s->wdata[1][s->j % 512 * s->wsl[1] +
			s->cox % 512 * s->wbpp[1] / 8], sizeof(int));
		s->j++;
	}
	s->j = s->drawStart;

	if (s->side == 0)
	{
		s->id = 3;
		s->x_wall = s->posY + s->perpWallDist * s->rayDirY;
	}
	else
	{
		s->id = 4;
		s->x_wall = s->posX + s->perpWallDist * s->rayDirX;
	}
	if (s->side == 0 && s->rayDirX > 0)
		s->id = 2;
	auxline(s);
}
