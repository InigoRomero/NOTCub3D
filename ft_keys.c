/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 11:25:22 by iromero-          #+#    #+#             */
/*   Updated: 2020/01/04 19:02:55 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	w_and_s(t_mapinfo *s)
{
	if (s->presedw == 1)
	{
		if ((s->mapn[(int)(s->posx + s->dirx *
			(s->movespeed + 0.6))][(int)s->posy]) != 1)
			s->posx += s->dirx * s->movespeed;
		if ((s->mapn[(int)s->posx][(int)(s->posy + s->diry *
			(s->movespeed + 0.6))]) != 1)
			s->posy += s->diry * s->movespeed;
	}
	if (s->preseds == 1)
	{
		if ((s->mapn[(int)(s->posx - s->dirx *
			(s->movespeed + 0.6))][(int)s->posy]) != 1)
			s->posx -= s->dirx * s->movespeed;
		if ((s->mapn[(int)s->posx][(int)(s->posy -
			s->diry * (s->movespeed + 0.6))]) != 1)
			s->posy -= s->diry * s->movespeed;
	}
}

void	a_and_d(t_mapinfo *s)
{
	if (s->preseda == 1)
	{
		if ((s->mapn[(int)(s->posx - s->diry *
			(s->movespeed + 0.6))][(int)s->posy]) != 1)
			s->posx -= s->diry * s->movespeed;
		if ((s->mapn[(int)s->posx][(int)(s->posy +
			s->dirx * (s->movespeed + 0.6))]) != 1)
			s->posy += s->dirx * s->movespeed;
	}
	if (s->presedd == 1)
	{
		if ((s->mapn[(int)(s->posx + s->diry *
			(s->movespeed + 0.6))][(int)s->posy]) != 1)
			s->posx += s->diry * s->movespeed;
		if ((s->mapn[(int)s->posx][(int)(s->posy -
			s->dirx * (s->movespeed + 0.6))]) != 1)
			s->posy -= s->dirx * s->movespeed;
	}
}

void	l_and_r(t_mapinfo *s)
{
	if (s->presedl == 1)
	{
		s->olddirx = s->dirx;
		s->dirx = s->dirx * cos(s->rotspeed) - s->diry * sin(s->rotspeed);
		s->diry = s->olddirx * sin(s->rotspeed) + s->diry * cos(s->rotspeed);
		s->oldplanex = s->planex;
		s->planex = s->planex * cos(-s->rotspeed)
			- s->planey * sin(s->rotspeed);
		s->planey = s->oldplanex * sin(s->rotspeed)
			+ s->planey * cos(-s->rotspeed);
	}
	if (s->presedr == 1)
	{
		s->olddirx = s->dirx;
		s->dirx = s->dirx * cos(-s->rotspeed) - s->diry * sin(-s->rotspeed);
		s->diry = s->olddirx * sin(-s->rotspeed) + s->diry * cos(-s->rotspeed);
		s->oldplanex = s->planex;
		s->planex = s->planex * cos(-s->rotspeed) -
			s->planey * sin(-s->rotspeed);
		s->planey = s->oldplanex * sin(-s->rotspeed)
			+ s->planey * cos(-s->rotspeed);
	}
}

int		deal_key(t_mapinfo *s)
{
	double p;

	p = -0.40;
	raycasting(s);
	w_and_s(s);
	a_and_d(s);
	l_and_r(s);
	if (s->presedesq == 1)
	{
		free(s);
		system("leaks CUB3D");
		exit(1);
	}
	return (1);
}
