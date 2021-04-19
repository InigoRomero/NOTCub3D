/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 19:38:44 by iromero-          #+#    #+#             */
/*   Updated: 2021/04/19 17:06:46 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	put_pxl_to_img(t_s *s, int x, int y)
{
	int n;

	if (x < s->x && y < s->y)
	{
		n = abs((((y * (s->h[s->id] * 4) - s->y * (s->h[s->id] * 2)
			+ s->lineheight * (s->h[s->id] * 2)) * s->h[s->id])
					/ s->lineheight) / (s->h[s->id] * 4));
		ft_memcpy(s->img_ptr + (s->wbpp[s->id] / 8) * s->x * y
			+ x * (s->wbpp[s->id] / 8),
				&s->wdata[s->id][n % s->h[s->id] * s->wsl[s->id] +
				s->x_text % s->w[s->id] * s->wbpp[s->id] / 8], sizeof(int));
	}
}

void	printhp(t_s *s)
{
	int j;

	j = 60;
	while (j - 60 < (int)s->hp)
	{
		ft_memcpy(s->img_ptr + 4 * s->x * 10 + j * 4, &s->color2, sizeof(int));
		ft_memcpy(s->img_ptr + 4 * s->x * 11 + j * 4, &s->color2, sizeof(int));
		ft_memcpy(s->img_ptr + 4 * s->x * 12 + j * 4, &s->color2, sizeof(int));
		ft_memcpy(s->img_ptr + 4 * s->x * 13 + j * 4, &s->color2, sizeof(int));
		ft_memcpy(s->img_ptr + 4 * s->x * 14 + j * 4, &s->color2, sizeof(int));
		ft_memcpy(s->img_ptr + 4 * s->x * 15 + j * 4, &s->color2, sizeof(int));
		j++;
	}
}

void	auxline(t_s *s)
{
	if (s->side == 1 && s->raydiry < 0)
		s->id = 0;
	s->x_text = (int)(s->x_wall * (double)s->w[s->id]);
	s->x_text = abs(s->x_text);
	while (s->j <= s->drawend)
		put_pxl_to_img(s, s->cox, s->j++);
	while (s->j < s->y)
	{
		ft_memcpy(s->img_ptr + 4 * s->x * s->j +
			s->cox * 4, &s->color2, sizeof(int));
		s->j++;
	}
	printhp(s);
}

void	ft_verline(t_s *s)
{
	s->color2 = 293994;
	s->j = 0;
	while (s->j < s->drawstart)
	{
		ft_memcpy(s->img_ptr + (s->wbpp[1] / 8) * s->x *
			s->j + s->cox * (s->wbpp[1] / 8),
			&s->wdata[1][s->j % 512 * s->wsl[1] +
			s->cox % 512 * s->wbpp[1] / 8], sizeof(int));
		s->j++;
	}
	s->j = s->drawstart;
	if (s->side == 0)
	{
		s->id = 3;
		s->x_wall = s->posy + s->perpwalldist * s->raydiry;
	}
	else
	{
		s->id = 4;
		s->x_wall = s->posx + s->perpwalldist * s->raydirx;
	}
	if (s->side == 0 && s->raydirx > 0)
		s->id = 2;
	auxline(s);
}
