/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 14:29:36 by iromero-          #+#    #+#             */
/*   Updated: 2020/01/06 18:13:09 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	readmap(t_mapinfo *s, char **argv, int argc)
{
	int		fp;
	char	*buffer;

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
	close(fp);
	if (argc == 3)
		s->screenshot = 1;
	if (argc == 3 && ft_strncmp(argv[2], "--save", 6))
	{
		write(1, "mal argumento", 13);
		exit(1);
	}
}

void	startvars(t_mapinfo *s)
{
	s->id = 0;
	s->planex = 0;
	s->planey = 0.66;
	s->obj = 0;
	s->movespeed = 0.12;
	s->rotspeed = 0.08;
	s->count = 0;
	s->mlx_ptr = NULL;
	s->win_ptr = NULL;
	s->score = 0;
	s->hp = 200.00;
}

void	openall(t_mapinfo *s)
{
	int i;

	i = 0;
	s->mlx_ptr = mlx_init();
	s->win_ptr = mlx_new_window(s->mlx_ptr, s->x, s->y, "mlx 42");
	fp(s);
	s->fpposx = s->x / 2 - s->w[5] / 2;
	s->fpposy = s->y - s->h[5];
	raycasting(s);
	mlx_hook(s->win_ptr, 2, 0, nopulsed, s);
	mlx_hook(s->win_ptr, 3, 0, pulsed, s);
	mlx_loop_hook(s->mlx_ptr, deal_key, s);
	if (s->initialdir > 0)
	{
		s->presedl = 1;
		while (i++ < s->initialdir)
			deal_key(s);
		s->presedl = 0;
		s->initialdir = 0;
	}
	mlx_loop(s->mlx_ptr);
}
