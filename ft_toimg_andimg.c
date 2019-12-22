/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toimg_andimg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 13:15:30 by iromero-          #+#    #+#             */
/*   Updated: 2019/12/22 14:27:52 by iromero-         ###   ########.fr       */
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
		s->obend = s->alturalinea / 2 + (s->y / 1.3);
		if (s->obend >= s->y)
			s->obend = s->y - 1;
	}
}

void	to_img(t_mapinfo *s)
{
	s->count = 0;
	mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->img, 0, 0);
	mlx_put_image_to_window(s->mlx_ptr, s->win_ptr,
		s->wlone[5], s->fpposx, s->fpposy);
	if (s->obj == 1)
		mlx_put_image_to_window(s->mlx_ptr, s->win_ptr,
			s->wlone[7], s->obstart, s->obend);
	mlx_string_put(s->mlx_ptr, s->win_ptr, 20, 20, 293994, ft_itoa(s->score));
	mlx_destroy_image(s->mlx_ptr, s->wlone[7]);
	mlx_destroy_image(s->mlx_ptr, s->img);
	s->obj = 0;
}
