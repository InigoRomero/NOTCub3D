/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 16:08:19 by iromero-          #+#    #+#             */
/*   Updated: 2019/12/14 18:57:09 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int ft_rgb_color_int(int r, int g, int b)
{
    return ((r << 16) + (g << 8) + b);
}

void	fp(t_mapinfo *s)
{
	int x;
	int y;

	x = s->x / 2;
	y = s->y / 2;
	char *str;
	str = ft_strdup("src/fp2.xpm");
	s->img_psr = mlx_xpm_file_to_image(s->mlx_ptr, str, &x, &y);
	s->img_psrda = mlx_get_data_addr(s->img_psr, &s->bpp, &s->sl, &s->endian);
}
void	ft_verLine(int x, int start, int end, int color, t_mapinfo *s)
{
	int j;
	int color2;

	color2 = 293994;
	j = 0;
	while (j < start)
	{
		ft_memcpy(s->img_ptr + 4 * s->x * j + x * 4, &color2, sizeof(int));
		j++;
	}
	j = start;
	while (j < end)
	{
		ft_memcpy(s->img_ptr + 4 * s->x * j + x * 4, &color, sizeof(int));
		j++;
	}
	j = end;
	ft_strjoin(s->img_ptr, s->img_psr);
	while (j < s->y)
	{
		ft_memcpy(s->img_ptr + 4 * s->x * j + x * 4, &color2, sizeof(int));
		j++;
	}

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
	s->planeY = 0.66;
	s->moveSpeed = 0.08;
	s->rotSpeed = 0.05;
	/*s->width = 400;
	s->height = 400;
	s->bpp = 0;
	s->size_line = 0;
	s->endian = 0;
	char *pop;

	pop = ft_strdup("wall.xpm");
	tru->img = mlx_xpm_to_image(s->mlx_ptr, &pop,&s->width, &s->height);
	mlx_get_data_addr(s->img,  &s->bpp, &s->size_line, &s->endian);*/
}

void	raycasting(t_mapinfo *s)
{
	int n;

	n = 0;
	s->img = mlx_new_image(s->mlx_ptr, s->x, s->y);
	s->img_ptr = mlx_get_data_addr(s->img, &s->bpp, &s->sl, &s->endian);
	printf("x:%f  y:%f\n", s->dirX, s->dirY);
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
	//fp(s);
	mlx_put_image_to_window(s->mlx_ptr, s->win_ptr,  s->img, 0, 0 );
	mlx_put_image_to_window(s->mlx_ptr, s->win_ptr,  s->img_psr, s->x / 3, s->y - s->y / 3);
	mlx_destroy_image(s->mlx_ptr, s->img);
	//mlx_destroy_image(s->mlx_ptr, s->img_psr);
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
		s->moveSpeed = 0.08;
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
		s->moveSpeed = 0.16;
	return (0);
}

int		deal_key(t_mapinfo *s)
{
	double p;

	p = -0.40;
	if (s->presedw == 1)
	{
		if (!(s->mapn[(int)(s->posX + s->dirX * s->moveSpeed)][(int)s->posY]))
			s->posX += s->dirX * s->moveSpeed;
		if(!(s->mapn[(int)s->posX][(int)(s->posY + s->dirY * s->moveSpeed)]))
			s->posY += s->dirY * s->moveSpeed;
	}
	if (s->preseds == 1)
	{
		if (!(s->mapn[(int)(s->posX - s->dirX * s->moveSpeed)][(int)s->posY]))
			s->posX -= s->dirX * s->moveSpeed;
		if (!(s->mapn[(int)s->posX][(int)(s->posY - s->dirY * s->moveSpeed)]))
			s->posY -= s->dirY * s->moveSpeed;
	}
	if (s->preseda == 1)
	{
		if (!(s->mapn[(int)(s->posX - s->dirY * s->moveSpeed)][(int)s->posY]))
			s->posX -= s->dirY * s->moveSpeed;
		if(!(s->mapn[(int)s->posX][(int)(s->posY + s->dirX * s->moveSpeed)]))
			s->posY += s->dirX * s->moveSpeed;
	}
	if (s->presedd == 1)
	{

		if (!(s->mapn[(int)(s->posX + s->dirY * s->moveSpeed)][(int)s->posY]))
			s->posX += s->dirY * s->moveSpeed;
		if(!(s->mapn[(int)s->posX][(int)(s->posY - s->dirX * s->moveSpeed)]))
			s->posY -= s->dirX * s->moveSpeed;
	}
	if (s->presedl == 1)
	{
		s->oldDirX = s->dirX;
		s->dirX = s->dirX * cos(s->rotSpeed) - s->dirY * sin(s->rotSpeed);
		s->dirY = s->oldDirX * sin(s->rotSpeed) + s->dirY * cos(s->rotSpeed);
		s->oldPlaneX = s->planeX;
		s->planeX = s->planeX * cos(-s->rotSpeed) - s->planeY * sin(s->rotSpeed);
		s->planeY = s->oldPlaneX * sin(s->rotSpeed) + s->planeY * cos(-s->rotSpeed);
	}
	if (s->presedr == 1)
	{
		s->oldDirX = s->dirX;
		s->dirX = s->dirX * cos(-s->rotSpeed) - s->dirY * sin(-s->rotSpeed);
		s->dirY = s->oldDirX * sin(-s->rotSpeed) + s->dirY * cos(-s->rotSpeed);
		s->oldPlaneX = s->planeX;
		s->planeX = s->planeX * cos(-s->rotSpeed) - s->planeY * sin(-s->rotSpeed);
		s->planeY = s->oldPlaneX * sin(-s->rotSpeed) + s->planeY * cos(-s->rotSpeed);
	}
	if (s->presedesq == 1)
		exit(1);
	raycasting(s);
	return (1);
}

void	openall(t_mapinfo *s)
{
	int i;

	i = 0;
	s->mlx_ptr = mlx_init();
	s->win_ptr = mlx_new_window(s->mlx_ptr, s->x, s->y, "mlx 42");
	fp(s);
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
