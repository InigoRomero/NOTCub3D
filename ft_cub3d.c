/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 16:08:19 by iromero-          #+#    #+#             */
/*   Updated: 2019/12/16 18:24:04 by iromero-         ###   ########.fr       */
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

	x = 64;
	y = 64;
	char *str;
	str = ft_strdup("src/fp2.xpm");
	s->img_psr = mlx_xpm_file_to_image(s->mlx_ptr, str, &x, &y);
	//s->img_psrda = mlx_get_data_addr(s->img_psr, &s->bpp, &s->sl, &s->endian);
	
	//str = ft_strdup("src/wall.xpm");
	s->wlone[0] = mlx_xpm_file_to_image(s->mlx_ptr, "src/stone.xpm", &x, &y);
	s->wdata[0] = mlx_get_data_addr(s->wlone[0], &s->wbpp[0], &s->wsl[0], &s->wendian[0]);
	x = 512;
	y = 512;
	s->wlone[1] = mlx_xpm_file_to_image(s->mlx_ptr, "src/sky.xpm", &x, &y);
	s->wdata[1] = mlx_get_data_addr(s->wlone[1], &s->wbpp[1], &s->wsl[1], &s->wendian[1]);
	x = 64;
	y = 64;
	s->wlone[2] = mlx_xpm_file_to_image(s->mlx_ptr, "src/wood.xpm", &x, &y);
	s->wdata[2] = mlx_get_data_addr(s->wlone[2], &s->wbpp[2], &s->wsl[2], &s->wendian[2]);
}

void	put_pxl_to_img(t_mapinfo *s, int x, int y)
{
	int n;
	
	if (x < s->x && y < s->y)
	{
		n = abs((((y * 256 - s->y * 128 + s->lineHeight * 128) * 64)
					/ s->lineHeight) / 256);
		ft_memcpy(s->img_ptr + 4 * s->x * y + x * 4,// &s->color, sizeof(int));
				&s->wdata[s->id][n % 64 * s->wsl[s->id] +
				s->x_text % 64 * s->wbpp[s->id] / 8], sizeof(int));
	}
}

void	ft_sky( t_mapinfo *s)
{
	int j;
	int p;

	p = 0;
	while (p < s->x)
	{
		j = 0;
		while (j < s->y / 2)
		{
			ft_memcpy(s->img_ptr + 4 * s->x * j + j * 4,
				&s->wdata[1][j % 512 * s->wsl[1] +
				p % 512 * s->wbpp[1] / 9], sizeof(int));
			j++;
		}
		p++;
	}
}
void	ft_verLine(int x, int start, int end, int color, t_mapinfo *s)
{
	int j;
	int color2;
	int count;
	
	count = 0;
	color2 = 293994;
	j = 0;
	while (j < start)
	{
		ft_memcpy(s->img_ptr + 4 * s->x * j + x * 4, &color2, sizeof(int));
		j++;
	}
	/*j = 0;
	while (j < start)
	{
		ft_memcpy(s->img_ptr + 4 * s->x * j + j * 4,
			&s->wdata[1][j % 512 * s->wsl[1] +
			x % 512 * s->wbpp[1] / 8], sizeof(int));
		j++;
	}*/
	j = start;

	if (s->side == 0)
		s->x_wall = s->posY + s->perpWallDist * s->rayDirY;
	else
		s->x_wall = s->posX + s->perpWallDist * s->rayDirX;
	s->x_text = (int)(s->x_wall * (double)(64));
	if (s->side == 0 && s->rayDirX > 0)
		s->x_text = 64 - s->x_text - 1;
	if (s->side == 1 && s->rayDirY < 0)
		s->x_text = 64 - s->x_text - 1;
	s->x_text = abs(s->x_text);
	while (j <= end)
		put_pxl_to_img(s, x, j++);

	/*while (j < end)
	{
		ft_memcpy(s->img_ptr + 4 * s->x * j + x * 4, &color, sizeof(int));
		j++;
	}*/
	j = end;
	//ft_strjoin(s->img_ptr, s->img_psr);
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
	//ft_sky(s);
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
			s->id = 0;
		if (s->side == 1)
			s->id = 2;
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
	raycasting(s);
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
