/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 15:04:33 by iromero-          #+#    #+#             */
/*   Updated: 2021/04/26 15:59:35 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int			noflines(t_s *s)
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

int			noffiles(t_s *s)
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

static void	getdirandpos(t_s *s, int dir, int x, int y)
{
	s->posx = x;
	s->posy = y;
	s->dirx = -1;
	s->diry = 0;
	s->planex = 0;
	s->planey = 0.66;
	if (dir == DIRS)
	{
		s->dirx = 1;
		s->diry = 0;
		s->planex = 0;
		s->planey = -0.66;
	}
	if (dir == DIRW)
	{
		s->dirx = 0;
		s->diry = -1;
		s->planex = -0.66;
		s->planey = 0;
	}
	 if (dir == DIRE)
	{
		s->dirx = 0;
		s->diry = 1;
		s->planex = 0.66;
		s->planey = 0;
	}

}

void		maptoarrayaux(t_s *s, int i, int n, int y)
{
	s->mapn[i][y] = s->map[n] - 48;
	if (s->mapn[i][y] == 2 || s->mapn[i][y] == 3 || s->mapn[i][y] == 4)
		s->count_sprite++;
	if (s->mapn[i][y] > 4)
	{
		getdirandpos(s, s->mapn[i][y], i, y);
		s->mapn[i][y] = 0;
	}
}

void		maptoarray(t_s *s)
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
		y = 0;
		if (!(s->mapn[i] = malloc(sizeof(int) * (noffiles(s) + 1))))
			return ;
		while (y < noffiles(s))
		{
			maptoarrayaux(s, i, n, y++);
			n += 2;
		}
		i++;
	}
}
