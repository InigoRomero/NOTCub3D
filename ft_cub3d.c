/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 18:38:25 by iromero-          #+#    #+#             */
/*   Updated: 2019/12/21 19:39:32 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int ft_rgb_color_int(int r, int g, int b)
{
    return ((r << 16) + (g << 8) + b);
}

void	fp(t_mapinfo *s)
{
	s->wlone[0] = mlx_xpm_file_to_image(s->mlx_ptr, s->ea, &s->w[0], &s->h[0]);
	s->wdata[0] = mlx_get_data_addr(s->wlone[0], &s->wbpp[0], &s->wsl[0], &s->wendian[0]);
	s->wlone[1] = mlx_xpm_file_to_image(s->mlx_ptr, "src/sky.xpm", &s->w[1], &s->h[1]);
	s->wdata[1] = mlx_get_data_addr(s->wlone[1], &s->wbpp[1], &s->wsl[1], &s->wendian[1]);
	s->wlone[2] = mlx_xpm_file_to_image(s->mlx_ptr, s->no, &s->w[2], &s->h[2]);
	s->wdata[2] = mlx_get_data_addr(s->wlone[2], &s->wbpp[2], &s->wsl[2], &s->wendian[2]);
	s->wlone[3] = mlx_xpm_file_to_image(s->mlx_ptr, s->so, &s->w[3], &s->h[3]);
	s->wdata[3] = mlx_get_data_addr(s->wlone[3], &s->wbpp[3], &s->wsl[3], &s->wendian[3]);
	s->wlone[4] = mlx_xpm_file_to_image(s->mlx_ptr, s->we, &s->w[4], &s->h[4]);
	s->wdata[4] = mlx_get_data_addr(s->wlone[4], &s->wbpp[4], &s->wsl[4], &s->wendian[4]);
	s->wlone[5] = mlx_xpm_file_to_image(s->mlx_ptr, "src/fp3.xpm", &s->w[5], &s->h[5]);
	s->wdata[5] = mlx_get_data_addr(s->wlone[5], &s->wbpp[5], &s->wsl[5], &s->wendian[5]);
	s->wlone[6] = mlx_xpm_file_to_image(s->mlx_ptr, "src/Floor.xpm", &s->w[6], &s->h[6]);
	s->wdata[6] = mlx_get_data_addr(s->wlone[6], &s->wbpp[6], &s->wsl[6], &s->wendian[6]);
	s->wlone[7] = mlx_xpm_file_to_image(s->mlx_ptr, "src/wood.xpm", &s->w[7], &s->h[7]);
	s->wdata[7] = mlx_get_data_addr(s->wlone[7], &s->wbpp[7], &s->wsl[7], &s->wendian[7]);
}

void	readmap(t_mapinfo *s, char **argv, int argc)
{
	int		fp;
	char	*buffer;

	s->map = ft_strdup("");
	fp = open(argv[argc - 1], O_RDONLY);
	while ((get_next_line(fp, &buffer)) != 0)
		getinfo(s, buffer);
	getinfo(s, buffer);
	maptoarray(s);
	close(fp);
}

void	startvars(t_mapinfo *s)
{
	s->width = 0;
	s->id = 0;
	s->height = 0;
	s->planeX = 0;
	s->planeY = 0.66;
	s->obj = 0;
	s->moveSpeed = 0.12;
	s->rotSpeed = 0.08;
	s->count = 0;
	s->mlx_ptr = NULL;
	s->win_ptr = NULL;
	s->score = 0;
}


 /*									TECLAS CHACHOOOOOOOOOOOO					*/
int		pulsed(int key, t_mapinfo *s)
{
	if (key == KEY_W)
		s->presedw = 0;
	if (key == KEY_S)
		s->preseds = 0;
	if (key == KEY_A)
		s->preseda = 0;
	if (key == KEY_D)
		s->presedd = 0;
	if (key == KEY_LEFT)
		s->presedl = 0;
	if (key == KEY_RIGHT)
		s->presedr = 0;
	if (key == KEY_ESQ)
		s->presedr = 0;
	if (key == KEY_SHIFT)
		s->moveSpeed = 0.12;
	return (0);
}

int		nopulsed(int key, t_mapinfo *s)
{
	if (key == KEY_W)
		s->presedw = 1;
	if (key == KEY_S)
		s->preseds = 1;
	if (key == KEY_A)
		s->preseda = 1;
	if (key == KEY_D)
		s->presedd = 1;
	if (key == KEY_LEFT)
		s->presedl = 1;
	if (key == KEY_RIGHT)
		s->presedr = 1;
	if (key == KEY_ESQ)
		s->presedesq = 1;
	if (key == KEY_SHIFT)
		s->moveSpeed = 0.35;
	return (0);
}



void	openall(t_mapinfo *s)
{
	int i;

	i = 0;
	s->mlx_ptr = mlx_init();
	s->win_ptr = mlx_new_window(s->mlx_ptr, s->x, s->y, "mlx 42");
	fp(s);
	s->fpposx = s-> x / 2 - s->w[5] / 2;
	s->fpposy = s->y - s->h[5];
	raycasting(s);
	mlx_hook(s->win_ptr, 2, 0,nopulsed, s);
	mlx_hook(s->win_ptr, 3, 0,pulsed, s);
	mlx_loop_hook(s->mlx_ptr, deal_key, s);
/*	if (s->initialdir > 0)
	{
		while (i++ < s->initialdir)
			deal_key(s);
		s->initialdir = 0;
	}*/
	mlx_loop(s->mlx_ptr);
}

int		main(int argc, char **argv)
{
	t_mapinfo *s;

	if (!(s = malloc(sizeof(*s))))
		return (-1);
	readmap(s, argv, argc);
	startvars(s);
	if (checkrules(s) == -1)
	{
		printf("bad map broh");
		return (-1);
	}
	openall(s);
	/*s->mlx_ptr = mlx_init();
	s->win_ptr = mlx_new_window(s->mlx_ptr, s->x, s->y, "mlx 42");
	mlx_key_hook(s->win_ptr, deal_key, s);
	raycasting(s);
	mlx_loop(s->mlx_ptr);*/
	return (0);
}
