/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 16:08:19 by iromero-          #+#    #+#             */
/*   Updated: 2019/12/07 21:32:42 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int		deal_key(int key, t_struct *stru)
{
	ft_putchar('X');
	return (0);
}

void	readmap(t_struct *stru, char **argv, int argc)
{
	int	fp;
	int n;
	char *buffer;


	stru->map = ft_strdup("");
	fp = open(argv[argc - 1], O_RDONLY);
	while ((get_next_line(fp, &buffer)) != 0)
	{
		getinfo(stru);
		stru->map = ft_strjoin(stru->map, buffer);
	}
	stru->map = ft_strjoin(stru->map, buffer);
	close(fp);
}

int		main(int argc, char **argv)
{
	t_struct *stru;

	if (!(stru = malloc(sizeof(*stru))))
		return (-1);
	readmap(stru, argv, argc);
	printf("\n -%s", stru->map);
	/*
	stru->mlx_ptr = mlx_init();
	stru->win_ptr = mlx_new_window(stru->mlx_ptr, 1920, 1080, "mlx 42");
	int x = 0;
	int y = 0;
	while (x++ < 250 && y++ < 250)
		mlx_pixel_put(stru->mlx_ptr, stru->win_ptr, x, y, 54);
	mlx_key_hook(stru->win_ptr, deal_key, stru);
	mlx_loop(stru->mlx_ptr);
	return (0);*/
}
