/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 16:08:19 by iromero-          #+#    #+#             */
/*   Updated: 2019/12/11 15:59:42 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int ft_rgb_color_int(int r, int g, int b)
{
    return ((r << 16) + (g << 8) + b);
}

/*void	rmall(t_mapinfo *stru)
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
}*/

void	ft_verLine(int x, int start, int end, int color, t_mapinfo *stru)
{
	while (start < end)
	{
		mlx_pixel_put(stru->mlx_ptr, stru->win_ptr, x, start, color);
		start++;
	}
}

int		deal_key(int key, t_mapinfo *stru)
{
	/*int i;

	i = 0;
	if (key == KEY_UP)
	{
		stru->width += 30;
		stru->height += 30;
		printwall(stru, stru->width, stru->height);
	}
	if (key == KEY_DOWN)
	{
		stru->width -= 30;
		stru->height -= 30;
		printwall(stru, stru->width, stru->height);
	}*/
	if (key == KEY_ESQ)
		exit(1);
	return (0);
}

void	readmap(t_mapinfo *stru, char **argv, int argc)
{
	int		fp;
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
	stru->width = 0;
	stru->height = 0;
	stru->planeX = 0;
	stru->planeY = 0.66;
	stru->time = 0;
	stru->oldtime = 0;
}

void	raycasting(t_mapinfo *stru)
{
	int n;

	n = 0;
	printf("%f", stru->dirY);
	while (n < stru->x)
	{
		stru->cameraX = 2 * n / (double)stru->x - 1;
		stru->rayDirX = stru->dirX + stru->planeX * stru->cameraX;
		stru->rayDirY = stru->dirY + stru->planeY * stru->cameraX;
		stru->mapX = (int)stru->posX;
		stru->mapY = (int)stru->posY;
		stru->deltaDistX = fabs((1 / stru->rayDirX));
		stru->deltaDistY = fabs((1 / stru->rayDirY));
		stru->hit = 0;
		if (stru->rayDirX < 0)
		{
			stru->stepX = -1;
			stru->sideDistX = (stru->posX - stru->mapX) * stru->deltaDistX;
		}
		else
		{
			stru->stepX = 1;
			stru->sideDistX = (stru->mapX + 1.0 - stru->posX) * stru->deltaDistX;
		}
		if (stru->rayDirY < 0)
		{
			stru->stepY = -1;
			stru->sideDistY = (stru->posY - stru->mapY) * stru->deltaDistY;
		}
		else
		{
			stru->stepY = 1;
			stru->sideDistY = (stru->mapY + 1.0 - stru->posY) * stru->deltaDistY;
		}
		while (stru->hit == 0)
		{
			if (stru->sideDistX < stru->sideDistY)
			{
				stru->sideDistX += stru->deltaDistX;
				stru->mapX += stru->stepX;
				stru->side = 0;
			}
			else
			{
				stru->sideDistY += stru->deltaDistY;
				stru->mapY += stru->stepY;
				stru->side = 1;
			}
			if (stru->mapn[stru->mapX][stru->mapY] > 0)
				stru->hit = 1;
		}
		if (stru->side == 0)
			stru->perpWallDist = (stru->mapX - stru->posX + (1 - stru->stepX) / 2) / stru->rayDirX;
		else
		  	stru->perpWallDist = (stru->mapY - stru->posY + (1 - stru->stepY) / 2) / stru->rayDirY;
		stru->lineHeight = (int)(stru->y / stru->perpWallDist);
		stru->drawStart = -stru->lineHeight / 2 + stru->y  / 2;
		if (stru->drawStart < 0)
			stru->drawStart = 0;
		stru->drawEnd = stru->lineHeight / 2 + stru->y  / 2;
		if (stru->drawEnd >= stru->y )
			stru->drawEnd = stru->y - 1;
		if (stru->mapn[stru->mapX][stru->mapY] == 1)
			stru->color = 14753280;
		else if (stru->mapn[stru->mapX][stru->mapY] == 2)
			stru->color = 255;
		else
			stru->color = 14753280;
		if (stru->side == 1)
			stru->color = stru->color / 2;
      ft_verLine(n, stru->drawStart, stru->drawEnd, stru->color, stru);
	  n++;
	}
}

int		main(int argc, char **argv)
{
	t_mapinfo *stru;

	if (!(stru = malloc(sizeof(*stru))))
		return (-1);
	readmap(stru, argv, argc);
	startvars(stru);
	if (checkrules(stru) == -1)
	{
		printf("bad map broh");
		return (-1);
	}
	stru->mlx_ptr = mlx_init();
	stru->win_ptr = mlx_new_window(stru->mlx_ptr, stru->x, stru->y, "mlx 42");
	raycasting(stru);
	mlx_key_hook(stru->win_ptr, deal_key, stru);
	mlx_loop(stru->mlx_ptr);
	return (0);
}
