/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 14:29:36 by iromero-          #+#    #+#             */
/*   Updated: 2021/04/21 17:19:03 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	readmap(t_s *s, char **argv, int argc)
{
	int		fp;
	char	*buffer;

	s->count_sprite = 0;
	s->map = ft_strdup("");
	fp = open(argv[1], O_RDONLY);
	while ((get_next_line(fp, &buffer)) > 0)
	{
		getinfo(s, buffer);
		free(buffer);
	}
	getinfo(s, buffer);
	free(buffer);
	maptoarray(s);
	get_sprite(s);
	close(fp);
	if (argc == 3)
		s->screenshot = 1;
	if (argc == 3 && ft_strncmp(argv[2], "--save", 6))
	{
		write(1, "mal argumento", 13);
		exit(1);
	}
}

void	startvars(t_s *s)
{
	s->id = 0;
	s->movespeed = 0.12;
	s->rotspeed = 0.08;
	s->count = 0;
	s->mlx_ptr = NULL;
	s->win_ptr = NULL;
	s->score = 0;
	s->hp = 200.00;
}

void	openall(t_s *s)
{
	int i;

	i = 0;
	s->mlx_ptr = mlx_init();
	s->win_ptr = mlx_new_window(s->mlx_ptr, s->x, s->y, "mlx 42");
	s->img = mlx_new_image(s->mlx_ptr, s->x, s->y);
	s->img_ptr = mlx_get_data_addr(s->img, &s->bpp, &s->sl, &s->endian);
	fp(s);
	raycasting(s);
	mlx_hook(s->win_ptr, 2, 0, nopulsed, s);
	mlx_hook(s->win_ptr, 3, 0, pulsed, s);
	mlx_loop_hook(s->mlx_ptr, deal_key, s);
	mlx_loop(s->mlx_ptr);
}
