/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 15:04:33 by iromero-          #+#    #+#             */
/*   Updated: 2019/12/11 20:00:11 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int			noflines(t_mapinfo *stru)
{
	int i;
	int x;

	i = 0;
	x = 0;
	while (stru->map[i++] != '\0')
		if (stru->map[i] == '\n')
			x++;
	stru->height = x;
	return (x);
}

int			noffiles(t_mapinfo *stru)
{
	int i;
	int x;

	x = 0;
	i = 0;
	while (stru->map[i++] != '\n')
		if (stru->map[i] != ' ')
			x++;
	stru->width = x;
	return (x);
}

static void	getdirandpos(t_mapinfo *stru, int dir, int x, int y)
{
	stru->posX = x;
	stru->posY = y;
	stru->dirX = -1;
	stru->dirY = 0;
	if (dir == DIRN)
		stru->initialdir = 0;
	if (dir == DIRS)
		stru->initialdir = 8;
	if (dir == DIRW)
		stru->initialdir = 4;
	if (dir == DIRE)
		stru->initialdir = 12;
}

void		maptoarray(t_mapinfo *stru)
{
	int i;
	int n;
	int y;

	i = 0;
	n = 0;
	if (!(stru->mapn = malloc(sizeof(int *) * (noflines(stru) + 1))))
		return ;
	while (i < noflines(stru))
	{
		if (!(stru->mapn[i] = malloc(sizeof(int) * (noffiles(stru) + 1))))
			return ;
		y = 0;
		while (y < noffiles(stru))
		{
			stru->mapn[i][y] = stru->map[n] - 48;
			n += 2;
			if (stru->mapn[i][y] > 2)
			{
				getdirandpos(stru, stru->mapn[i][y], i, y);
				stru->mapn[i][y] = 0;
			}
			y++;
		}
		i++;
	}
}
