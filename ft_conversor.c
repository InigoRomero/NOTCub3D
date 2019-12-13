/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 15:04:33 by iromero-          #+#    #+#             */
/*   Updated: 2019/12/13 16:56:45 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int			noflines(t_mapinfo *s)
{
	int i;
	int x;

	i = 0;
	x = 0;
	while (s->map[i++] != '\0')
		if (s->map[i] == '\n')
			x++;
	s->height = x;
	return (x);
}

int			noffiles(t_mapinfo *s)
{
	int i;
	int x;

	x = 0;
	i = 0;
	while (s->map[i++] != '\n')
		if (s->map[i] != ' ')
			x++;
	s->width = x;
	return (x);
}

static void	getdirandpos(t_mapinfo *s, int dir, int x, int y)
{
	s->posX = x;
	s->posY = y;
	s->dirX = -1;
	s->dirY = 0;
	if (dir == DIRN)
		s->initialdir = 0;
	if (dir == DIRS)
		s->initialdir = 12;
	if (dir == DIRW)
		s->initialdir = 6;
	if (dir == DIRE)
		s->initialdir = 19;
}

void		maptoarray(t_mapinfo *s)
{
	int i;
	int n;
	int y;

	i = 0;
	n = 0;
	if (!(s->mapn = malloc(sizeof(int *) * (noflines(s) + 1))))
		return ;
	while (i < noflines(s))
	{
		if (!(s->mapn[i] = malloc(sizeof(int) * (noffiles(s) + 1))))
			return ;
		y = 0;
		while (y < noffiles(s))
		{
			s->mapn[i][y] = s->map[n] - 48;
			n += 2;
			if (s->mapn[i][y] == 2)
				s->mapn[i][y] = -1;
			if (s->mapn[i][y] > 2)
			{
				getdirandpos(s, s->mapn[i][y], i, y);
				s->mapn[i][y] = 0;
			}
			y++;
		}
		i++;
	}
}
