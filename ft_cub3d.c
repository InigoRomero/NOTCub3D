/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 16:08:19 by iromero-          #+#    #+#             */
/*   Updated: 2019/12/09 12:55:11 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		deal_key(int key, t_mapinfo *stru)
{
	if (key == KEY_LEFT)
		mlx_pixel_put(stru->mlx_ptr, stru->win_ptr, stru->posX--, stru->posY, 233);
	if (key == KEY_RIGHT)
		mlx_pixel_put(stru->mlx_ptr, stru->win_ptr, stru->posX++, stru->posY, 233);
	if (key == KEY_DOWN)
		mlx_pixel_put(stru->mlx_ptr, stru->win_ptr, stru->posX, stru->posY++, 233);
	if (key == KEY_UP)
		mlx_pixel_put(stru->mlx_ptr, stru->win_ptr, stru->posX, stru->posY--, 233);
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
	stru->posX = 47;
	stru->posY = 89;
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
	mlx_key_hook(stru->win_ptr, deal_key, stru);
	mlx_loop(stru->mlx_ptr);
	return (0);
}
