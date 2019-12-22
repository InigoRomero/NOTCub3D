/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rules.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 19:46:46 by iromero-          #+#    #+#             */
/*   Updated: 2019/12/22 17:24:32 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

static int	checkborder(t_mapinfo *s)
{
	int i;

	i = 0;
	while (i < s->width)
		if (s->mapn[0][i++] != 1)
			return (-1);
	i = 0;
	while (i < s->width)
		if (s->mapn[s->height - 1][i++] != 1)
			return (-1);
	i = 0;
	while (i < s->height)
		if (s->mapn[i++][0] != 1)
			return (-1);
	i = 0;
	while (i < s->height)
		if (s->mapn[i++][s->width - 1] != 1)
			return (-1);
	return (1);
}

static int	checkcontent(t_mapinfo *s)
{
	int i;

	i = 0;
	while (s->map[i] != '\0')
	{
		if (s->map[i] != '1' && s->map[i] != '0' && s->map[i] != '2'
			&& s->map[i] != 'N' && s->map[i] != 'S' &&
			s->map[i] != 'O' && s->map[i] != 'E' && s->map[i] != 'W')
			return (-1);
		i += 2;
	}
	return (1);
}

int			checkname(char **argv)
{
	char *aux;

	aux = ft_strdup(argv[1]);
	if (!(aux = ft_strchr(aux, '.')))
		return (-1);
	*aux = 0;
	if (*(++aux) != 'c')
		return (-1);
	if (*(++aux) != 'u')
		return (-1);
	if (*(++aux) != 'b')
		return (-1);
	return (1);
}

int			checkrules(t_mapinfo *s)
{
	if (checkborder(s) == -1)
		return (-1);
	if (checkcontent(s) == -1)
		return (-1);
	if (!(ft_strchr(s->map, 'N') || ft_strchr(s->map, 'S') ||
		ft_strchr(s->map, 'W') || ft_strchr(s->map, 'E')))
		return (-1);
	return (1);
}
