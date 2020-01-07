/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toimg_andimg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 13:15:30 by iromero-          #+#    #+#             */
/*   Updated: 2020/01/06 19:15:41 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	calcularobj(t_mapinfo *s)
{
	while (s->obend - s->obstart < s->h[7])
	{
		s->alturalinea = s->drawend - s->h[7];
		s->obstart = -s->alturalinea / 2 + (s->y / 1.3);
		if (s->obstart < 0)
			s->obstart = 0;
		s->obend = s->alturalinea / 2 + (s->y / 1.3);
		if (s->obend >= s->y)
			s->obend = s->y - 1;
	}
}

void	set_int_in_char(unsigned char *start, int value)
{
	start[0] = (unsigned char)(value);
	start[1] = (unsigned char)(value >> 8);
	start[2] = (unsigned char)(value >> 16);
	start[3] = (unsigned char)(value >> 24);
}

int		get_color(t_mapinfo *s, int x, int y)
{
	int	rgb;
	int	color;

	color = *(int*)(s->img_ptr
			+ (4 * (int)s->x * ((int)s->y - 1 - y))
			+ (4 * x));
	rgb = (color & 0xFF0000) | (color & 0x00FF00) | (color & 0x0000FF);
	return (rgb);
}

int		doscreenshot(t_mapinfo *s)
{
	int file;
	int filesize;
	int	pad;

	pad = (4 - ((int)s->x * 3) % 4) % 4;
	filesize = 54 + (3 * ((int)s->x + pad) * (int)s->y);
	if ((file = open("screenshot.bmp", O_WRONLY | O_CREAT
		| O_TRUNC | O_APPEND, 777)) < 0)
		return (0);
	if (!write_bmp_header(file, filesize, s))
		return (0);
	if (!write_bmp_data(file, s, pad))
		return (0);
	close(file);
	return (1);
}

void	to_img(t_mapinfo *s)
{
	char *n;

	s->count = 0;
	mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->img, 0, 0);
	mlx_put_image_to_window(s->mlx_ptr, s->win_ptr,
		s->wlone[5], s->fpposx, s->fpposy);
	if (s->obj == 1)
		mlx_put_image_to_window(s->mlx_ptr, s->win_ptr,
			s->wlone[7], s->obstart, s->obend);
	if (s->screenshot == 1)
	{
		doscreenshot(s);
		exit(1);
	}
	n = ft_itoa(s->score);
	mlx_string_put(s->mlx_ptr, s->win_ptr, 20, 20, 293994, n);
	free(n);
	mlx_destroy_image(s->mlx_ptr, s->wlone[7]);
	mlx_destroy_image(s->mlx_ptr, s->img);
	s->obj = 0;
}