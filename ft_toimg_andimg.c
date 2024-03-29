/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toimg_andimg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 13:15:30 by iromero-          #+#    #+#             */
/*   Updated: 2021/12/22 18:04:03 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	set_int_in_char(unsigned char *start, int value)
{
	start[0] = (unsigned char)(value);
	start[1] = (unsigned char)(value >> 8);
	start[2] = (unsigned char)(value >> 16);
	start[3] = (unsigned char)(value >> 24);
}

int		get_color(t_s *s, int x, int y)
{
	int	rgb;
	int	color;

	color = *(int*)(s->img_ptr
			+ (4 * (int)s->x * ((int)s->y - 1 - y))
			+ (4 * x));
	rgb = (color & 0xFF0000) | (color & 0x00FF00) | (color & 0x0000FF);
	return (rgb);
}

int		doscreenshot(t_s *s)
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

void	to_img(t_s *s)
{
	char *n;

	s->count = 0;
	mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->img, 0, 0);
	free(s->s_buff);
	if (s->screenshot == 1)
	{
		doscreenshot(s);
		exit(1);
	}
	n = ft_itoa(s->score);
	mlx_string_put(s->mlx_ptr, s->win_ptr, 20, 20, 293994, n);
	//mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->s_img, 0, s->snow_height);
	if (s->coin_counter == 0)
	{
		mlx_string_put(s->mlx_ptr, s->win_ptr, 20, 40, 293994, "you have collected all the coins");
		mlx_string_put(s->mlx_ptr, s->win_ptr, 20, 60, 293994, "The pokemons won't hurt you anymore");
	}
	free(n);
	//mlx_destroy_image(s->mlx_ptr, s->img);
}
