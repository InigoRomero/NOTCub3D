/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getinfo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 20:51:50 by iromero-          #+#    #+#             */
/*   Updated: 2019/12/09 12:26:19 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

static	void	getres(char *temp, t_mapinfo *stru)
{
	int i;
	int aux;

	i = 0;
	while (!(ft_isdigit(temp[i])))
		i++;
	aux = i;
	while (ft_isdigit(temp[i]))
		i++;
	stru->x = ft_atoi(ft_substr(temp, aux, i));
	while (temp[i] == ' ')
		i++;
	aux = i;
	while (ft_isdigit(temp[i]))
		i++;
	stru->y = ft_atoi(ft_substr(temp, aux, i));
}

static	char	*getstr(char *temp, t_mapinfo *stru)
{
	while (*temp != '.')
		temp++;
	return (ft_strdup(temp));
}

static	char	*getcolor(char *temp, t_mapinfo *stru)
{
	while (!(ft_isdigit(*temp)))
		temp++;
	return (ft_strdup(temp));
}

void			getinfo(t_mapinfo *stru, char *buffer)
{
	char	*temp;
	int		len;

	len = ft_strlen(buffer);
	if ((temp = ft_strchr(buffer, 'R')))
		getres(buffer, stru);
	else if (ft_strnstr(buffer, "NO", len))
		stru->no = ft_strdup(getstr(buffer, stru));
	else if (ft_strnstr(buffer, "SO", len))
		stru->so = ft_strdup(getstr(buffer, stru));
	else if (ft_strnstr(buffer, "WE", len))
		stru->we = ft_strdup(getstr(buffer, stru));
	else if (ft_strnstr(buffer, "EA", len))
		stru->ea = ft_strdup(getstr(buffer, stru));
	else if ((temp = ft_strchr(buffer, 'S')))
		stru->s = ft_strdup(getstr(buffer, stru));
	else if ((temp = ft_strchr(buffer, 'F')))
		stru->f = ft_strdup(getcolor(buffer, stru));
	else if ((temp = ft_strchr(buffer, 'C')))
		stru->c = ft_strdup(getcolor(buffer, stru));
	else if ((temp = ft_strchr(buffer, '1')))
		stru->map = ft_strjoin(stru->map, ft_strjoin(buffer, "\n"));
}
