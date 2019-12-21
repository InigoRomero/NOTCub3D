
#include "ft_cub3d.h"
void	ft_verLline(int x, int start, int end, int color, t_mapinfo *s)
{
	int j;
	int color2;

	color2 = 293994;
	j = 0;
	/*while (j < start)
	{
		ft_memcpy(s->img_ptr + 4 * s->x * j + x * 4, &color2, sizeof(int));
		j++;
	}*/
	int p;

	p = 0;
		j = 0;
		while (j < s->drawStart)
		{
			ft_memcpy(s->img_ptr + (s->wbpp[1] / 8) * s->x * j + x * (s->wbpp[1] / 8),
				&s->wdata[1][j % 512 * s->wsl[1] +
				x % 512 * s->wbpp[1] / 8], sizeof(int));
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
	{
		s->id = 3;
		s->x_wall = s->posY + s->perpWallDist * s->rayDirY;
	}
	else
	{
		s->id = 4;
		s->x_wall = s->posX + s->perpWallDist * s->rayDirX;
	}
	if (s->side == 0 && s->rayDirX > 0)
		s->id = 2;
	if (s->side == 1 && s->rayDirY < 0)
		s->id = 0;
	s->x_text = (int)(s->x_wall * (double)s->w[s->id]);
	s->x_text = abs(s->x_text);
	while (j <= end)
		put_pxl_to_img(s, x, j++);

	/*while (j < end)
	{
		ft_memcpy(s->img_ptr + 4 * s->x * j + x * 4, &color, sizeof(int));
		j++;
	}*/
	int n;
	/*s->id = 6;
	while (j <= s->y)
	{
		if (x < s->x && j < s->y)
		{
			n = abs((((j * (s->h[s->id] * 4) - s->y * (s->h[s->id] * 2)  * (s->h[s->id] * 2)) * s->h[s->id])
						/ s->lineHeight) / (s->h[s->id] * 4));
			ft_memcpy(s->img_ptr + (s->wbpp[s->id] / 8) * s->x * j + x * (s->wbpp[s->id] / 8),
					&s->wdata[6][j % s->w[6] * s->wsl[6] +
					n % s->h[6] * s->wbpp[6] / 8], sizeof(int));
		}
		j++;
	}*/
	/*
	while (j < s->y)
	{
			ft_memcpy(s->img_ptr + (s->wbpp[6] / 8) * s->x * j + x * (s->wbpp[6] / 8),
			&s->wdata[6][j % s->w[6] * s->wsl[6] +
			x % s->h[6] * s->wbpp[6] / 8], sizeof(int));
		j++;
	}*/
	//ft_strjoin(s->img_ptr, s->img_psr);
	while (j < s->y)
	{
		ft_memcpy(s->img_ptr + 4 * s->x * j + x * 4, &color2, sizeof(int));
		j++;
	}

	//OBJETOSSSS
	if (s->obj == 1)
	{
		s->id = 7;
		s->count++;
		j = s->obstart;
		if (s->side == 0)
			s->x_wall = s->posY + s->perpWallDist * s->rayDirY;
		else
			s->x_wall = s->posX + s->perpWallDist * s->rayDirX;
		s->x_text = (int)(s->x_wall * (double)s->w[s->id]);
		s->x_text = abs(s->x_text);
		while (j < s->obend && j - s->obstart < s->h[7] && s->count < s->w[7])
		{
			if(s->wdata[7][s->oby % s->h[7] * s->wsl[7] +
			s->obx % s->w[7] * s->wbpp[7] / 8] != 0)
				ft_memcpy(s->img_ptr + (s->wbpp[7] / 8) * s->x * j + x * (s->wbpp[7] / 8),
				&s->wdata[7][s->oby % s->h[7] * s->wsl[7] +
				s->obx % s->w[7] * s->wbpp[7] / 8], sizeof(int));
			s->oby++;
			j++;
		}
		s->obx++;
	}
}