/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 16:08:19 by iromero-          #+#    #+#             */
/*   Updated: 2019/12/10 14:04:56 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	rmall(t_mapinfo *stru)
{
	int i;
	int n;

	i = 0;
	while (i < stru->y)
	{
		n = 0;
		while (n < stru->x)
			mlx_pixel_put(stru->mlx_ptr, stru->win_ptr, n++, i, 0);
		i++;
	}
}

void	printwall(t_mapinfo *stru, int width, int height)
{
	int i;
	int n;
	int aux1;
	int aux2;

	i = 0;
	rmall(stru);
	while (i < height)
	{
		n = 0;
		while (n < width / 2)
			mlx_pixel_put(stru->mlx_ptr, stru->win_ptr, stru->x / 2 + n++, stru->y / 2  -  height / 2 + i , 233);
		i++;
	}
	i = 0;
	while (i < height)
	{
		n = 0;
		while (n < width / 2)
			mlx_pixel_put(stru->mlx_ptr, stru->win_ptr, stru->x / 2 - n++, stru->y / 2 -  height / 2 + i , 233);
		i++;
	}
}

int		deal_key(int key, t_mapinfo *stru)
{
	int i;

	i = 0;
	if (key == KEY_UP)
	{
		stru->posX += 30;
		stru->posY += 30;
		printwall(stru, stru->posX, stru->posY);
	}
	if (key == KEY_DOWN)
	{
		stru->posX -= 30;
		stru->posY -= 30;
		printwall(stru, stru->posX, stru->posY);
	}
	if (key == KEY_ESQ)
		return(-1);
	return (0);
}

void	readmap(t_mapinfo *stru, char **argv, int argc)
{
	int		fp;
	int		n;
	char	*buffer;

	stru->map = ft_strdup("");
	fp = open(argv[argc - 1], O_RDONLY);
	while ((get_next_line(fp, &buffer)) != 0)
		getinfo(stru, buffer);
	getinfo(stru, buffer);
	maptoarray(stru);
	close(fp);
}

void	startvars(t_mapinfo *stru)
{
	stru->posX = 150;
	stru->posY = 100;
	stru->dirX = 0;
	stru->dirY = 0;
}

int		main(int argc, char **argv)
{
	t_mapinfo *stru;

	if (!(stru = malloc(sizeof(*stru))))
		return (-1);
	startvars(stru);
	readmap(stru, argv, argc);
	if (checkrules(stru) == -1)
	{
		printf("bad map broh");
		return (-1);
	}
	stru->mlx_ptr = mlx_init();
	stru->win_ptr = mlx_new_window(stru->mlx_ptr, stru->x, stru->y, "mlx 42");
	printwall(stru, stru->posX , stru->posY);
	mlx_key_hook(stru->win_ptr, deal_key, stru);
	mlx_loop(stru->mlx_ptr);
	return (0);
}
