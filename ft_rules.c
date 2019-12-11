/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rules.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 19:46:46 by iromero-          #+#    #+#             */
/*   Updated: 2019/12/11 16:07:01 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

static int	checkborder(t_mapinfo *stru)
{
	int i;

	i = 0;
	while (i < stru->width)
		if (stru->mapn[0][i++] != 1)
			return (-1);
	i = 0;
	while (i < stru->width)
		if (stru->mapn[stru->height - 1][i++] != 1)
			return (-1);
	i = 0;
	while (i < stru->height)
		if (stru->mapn[i++][0] != 1)
			return (-1);
	i = 0;
	while (i < stru->height)
		if (stru->mapn[i++][stru->width - 1] != 1)
			return (-1);
	return (1);
}

static int	checkcontent(t_mapinfo *stru)
{
	int i;

	i = 0;
	while (stru->map[i] != '\0')
	{
		if (stru->map[i] != '1' && stru->map[i] != '0' && stru->map[i] != '2'
			&& stru->map[i] != 'N' && stru->map[i] != 'S' &&
			stru->map[i] != 'O' && stru->map[i] != 'E' && stru->map[i] != 'W')
			return (-1);
		i += 2;
	}
	return (1);
}

int			checkrules(t_mapinfo *stru)
{
	if (checkborder(stru) == -1)
		return (-1);
	if (checkcontent(stru) == -1)
		return (-1);
	return (1);
}
