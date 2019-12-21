/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 11:25:22 by iromero-          #+#    #+#             */
/*   Updated: 2019/12/21 19:08:58 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		deal_key(t_mapinfo *s)
{
	double p;

	p = -0.40;
	raycasting(s);
	if (s->presedw == 1)
	{
		if ((s->mapn[(int)(s->posX + s->dirX * (s->moveSpeed + 0.6)) ][(int)s->posY]) != 1)
			s->posX += s->dirX * s->moveSpeed;
		if((s->mapn[(int)s->posX][(int)(s->posY + s->dirY * (s->moveSpeed + 0.6))]) != 1)
			s->posY += s->dirY * s->moveSpeed;
	}
	if (s->preseds == 1)
	{
		if ((s->mapn[(int)(s->posX - s->dirX * (s->moveSpeed + 0.6))][(int)s->posY]) != 1)
			s->posX -= s->dirX * s->moveSpeed;
		if ((s->mapn[(int)s->posX][(int)(s->posY - s->dirY * (s->moveSpeed + 0.6))]) != 1)
			s->posY -= s->dirY * s->moveSpeed;
	}
	if (s->preseda == 1)
	{
		if ((s->mapn[(int)(s->posX - s->dirY * (s->moveSpeed + 0.6))][(int)s->posY]) != 1)
			s->posX -= s->dirY * s->moveSpeed;
		if((s->mapn[(int)s->posX][(int)(s->posY + s->dirX * (s->moveSpeed + 0.6))]) != 1)
			s->posY += s->dirX * s->moveSpeed;
	}
	if (s->presedd == 1)
	{

		if ((s->mapn[(int)(s->posX + s->dirY * (s->moveSpeed + 0.6))][(int)s->posY]) != 1)
			s->posX += s->dirY * s->moveSpeed;
		if((s->mapn[(int)s->posX][(int)(s->posY - s->dirX * (s->moveSpeed + 0.6))]) != 1)
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