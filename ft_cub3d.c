/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 16:08:19 by iromero-          #+#    #+#             */
/*   Updated: 2019/12/13 16:32:31 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int ft_rgb_color_int(int r, int g, int b)
{
    return ((r << 16) + (g << 8) + b);
}

void	ft_verLine(int x, int start, int end, int color, t_mapinfo *s)
{
	int i;

	i = 0;
	/*while (i < start)
	{
		mlx_pixel_put(s->mlx_ptr, s->win_ptr, x, i + end, 304930);
		mlx_pixel_put(s->mlx_ptr, s->win_ptr, x, i++, 93999);
	}
	while (start < end)
		mlx_pixel_put(s->mlx_ptr, s->win_ptr, x, start++, color);*/
	/*while (i < start)
	{
		ft_memcpy(s->wallone, ft_strdup("128283"), 6);
	}
	while (start < end)
		mlx_pixel_put(s->mlx_ptr, s->win_ptr, x, start++, color);*/
	int j = start;
	while (j < end)
	{
		ft_memcpy(s->img_ptr + 4 * s->x * j + x * 4, &color, sizeof(int));
		j++;
	}
	j = start + x;

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
	s->height = 0;
	s->planeX = 0;
	s->planeY = 1.2;
	s->moveSpeed = 0.80;
	s->rotSpeed = 0.25;
	/*s->width = 400;
	s->height = 400;
	s->bpp = 0;
	s->size_line = 0;
	s->endian = 0;
	char *pop;

	pop = ft_strdup("wall.xpm");
	tru->wallone = mlx_xpm_to_image(s->mlx_ptr, &pop,&s->width, &s->height);
	mlx_get_data_addr(s->wallone,  &s->bpp, &s->size_line, &s->endian);*/
}

void	raycasting(t_mapinfo *s)
{
	int n;

	n = 0;
	s->wallone = mlx_new_image(s->mlx_ptr, s->x, s->y);
	s->img_ptr = mlx_get_data_addr(s->wallone, &s->bpp, &s->sl, &s->endian);
	while (n < s->x)
	{
		s->cameraX = 2 * n / (double)s->x - 1;
		s->rayDirX = s->dirX + s->planeX * s->cameraX;
		s->rayDirY = s->dirY + s->planeY * s->cameraX;
		s->mapX = (int)s->posX;
		s->mapY = (int)s->posY;
		s->deltaDistX = fabs((1 / s->rayDirX));
		s->deltaDistY = fabs((1 / s->rayDirY));
		s->hit = 0;
		if (s->rayDirX < 0)
		{
			s->stepX = -1;
			s->sideDistX = (s->posX - s->mapX) * s->deltaDistX;
		}
		else
		{
			s->stepX = 1;
			s->sideDistX = (s->mapX + 1.0 - s->posX) * s->deltaDistX;
		}
		if (s->rayDirY < 0)
		{
			s->stepY = -1;
			s->sideDistY = (s->posY - s->mapY) * s->deltaDistY;
		}
		else
		{
			s->stepY = 1;
			s->sideDistY = (s->mapY + 1.0 - s->posY) * s->deltaDistY;
		}
		while (s->hit == 0)
		{
			if (s->sideDistX < s->sideDistY)
			{
				s->sideDistX += s->deltaDistX;
				s->mapX += s->stepX;
				s->side = 0;
			}
			else
			{
				s->sideDistY += s->deltaDistY;
				s->mapY += s->stepY;
				s->side = 1;
			}
			if (s->mapn[s->mapX][s->mapY] == 1)
				s->hit = 1;
		}
		if (s->side == 0)
			s->perpWallDist = (s->mapX - s->posX + (1 - s->stepX) / 2) / s->rayDirX;
		else
			s->perpWallDist = (s->mapY - s->posY + (1 - s->stepY) / 2) / s->rayDirY;
		s->lineHeight = (int)(s->y / s->perpWallDist);
		s->drawStart = -s->lineHeight / 2 + s->y  / 2;
		if (s->drawStart < 0)
			s->drawStart = 0;
		s->drawEnd = s->lineHeight / 2 + s->y  / 2;
		if (s->drawEnd >= s->y)
			s->drawEnd = s->y - 1;
		if (s->mapn[s->mapX][s->mapY] == 1)
			s->color = 7484839;
		if (s->side == 1)
			s->color = s->color / 2;
		ft_verLine(n, s->drawStart, s->drawEnd, s->color, s);
		n++;
	}

}
 /*									TECLAS CHACHOOOOOOOOOOOO					*/
int		deal_key(int key, t_mapinfo *s)
{
	if (key == KEY_W)
	{
		if (!(s->mapn[(int)(s->posX + s->dirX * s->moveSpeed)][(int)s->posY]))
			s->posX += s->dirX * s->moveSpeed;
		if(!(s->mapn[(int)s->posX][(int)(s->posY + s->dirY * s->moveSpeed)]))
			s->posY += s->dirY * s->moveSpeed;
	}
	if (key == KEY_S)
	{
		if (!(s->mapn[(int)(s->posX - s->dirX * s->moveSpeed)][(int)s->posY]))
			s->posX -= s->dirX * s->moveSpeed;
		if (!(s->mapn[(int)s->posX][(int)(s->posY - s->dirY * s->moveSpeed)]))
			s->posY -= s->dirY * s->moveSpeed;
	}
	if (key == KEY_A)
	{
		if(!(s->mapn[(int)s->posX][(int)(s->posY + s->dirY * s->moveSpeed)]))
		{
			if (s->dirY < 0 && s->dirX < 0)
				s->posY += s->dirY * s->moveSpeed;
			else if (s->dirY > 0 && s->dirX > 0)
				s->posY -= s->dirY * s->moveSpeed;
			else if (s->dirX == -1.0000 && s->dirY == 0.0000)
				s->posY += s->dirX * s->moveSpeed;
			else if (s->dirX < 0.0000 && s->dirY > 0.0000)
				s->posX -= s->dirY * s->moveSpeed;
			else if (s->dirX > 0.0000 && s->dirY < 0.0000)
				s->posX += s->dirY * s->moveSpeed;
		}
	}
	if (key == KEY_D)
	{
		if(!(s->mapn[(int)s->posX][(int)(s->posY + s->dirY * s->moveSpeed)]))
		{
			if (s->dirY < 0)
				s->posY -= s->dirY * s->moveSpeed;
			else if (s->dirY > 0)
				s->posY += s->dirY * s->moveSpeed;
			else if (s->dirX == -1 && s->dirY == 0)
				s->posX += s->dirX * s->moveSpeed;
		}
	}
	if (key == KEY_LEFT)
	{
		s->oldDirX = s->dirX;
		s->dirX = s->dirX * cos(s->rotSpeed) - s->dirY * sin(s->rotSpeed);
		s->dirY = s->oldDirX * sin(s->rotSpeed) + s->dirY * cos(s->rotSpeed);
		s->oldPlaneX = s->planeX;
		s->planeX = s->planeX * cos(-s->rotSpeed) - s->planeY * sin(s->rotSpeed);
		s->planeY = s->oldPlaneX * sin(s->rotSpeed) + s->planeY * cos(-s->rotSpeed);
	}
	if (key == KEY_RIGHT)
	{
		s->oldDirX = s->dirX;
		s->dirX = s->dirX * cos(-s->rotSpeed) - s->dirY * sin(-s->rotSpeed);
		s->dirY = s->oldDirX * sin(-s->rotSpeed) + s->dirY * cos(-s->rotSpeed);
		s->oldPlaneX = s->planeX;
		s->planeX = s->planeX * cos(-s->rotSpeed) - s->planeY * sin(-s->rotSpeed);
		s->planeY = s->oldPlaneX * sin(-s->rotSpeed) + s->planeY * cos(-s->rotSpeed);
	}
	if (key == KEY_ESQ)
		exit(1);
		printf("x:%f   y:%f\n", s->dirX , s->dirY);
	raycasting(s);
	mlx_put_image_to_window(s->mlx_ptr, s->win_ptr,  s->wallone, 0, 0 );
	mlx_destroy_image(s->mlx_ptr, s->wallone);
	return (0);
}

void	openall(t_mapinfo *s)
{
	int i;

	i = 0;
	s->mlx_ptr = mlx_init();
	s->win_ptr = mlx_new_window(s->mlx_ptr, s->x, s->y, "mlx 42");
	s->wallone = mlx_new_image(s->mlx_ptr, s->x, s->y);
	s->img_ptr = mlx_get_data_addr(s->wallone, &s->bpp, &s->sl, &s->endian);
	raycasting(s);
	mlx_put_image_to_window(s->mlx_ptr, s->win_ptr,  s->wallone, 0, 0 );
	mlx_destroy_image(s->mlx_ptr, s->wallone);
	mlx_hook(s->win_ptr, 2, 0,deal_key, s);
	if (s->initialdir > 0)
	{
		while (i++ < s->initialdir)
			deal_key(KEY_LEFT, s);
		s->initialdir = 0;
	}
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
