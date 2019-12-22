/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getinfo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 20:51:50 by iromero-          #+#    #+#             */
/*   Updated: 2019/12/22 16:42:54 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

static	void	getres(char *temp, t_mapinfo *s)
{
	int i;
	int aux;

	i = 0;
	while (!(ft_isdigit(temp[i])))
		i++;
	aux = i;
	while (ft_isdigit(temp[i]))
		i++;
	s->x = ft_atoi(ft_substr(temp, aux, i));
	while (temp[i] == ' ')
		i++;
	aux = i;
	while (ft_isdigit(temp[i]))
		i++;
	s->y = ft_atoi(ft_substr(temp, aux, i));
}

static	char	*getstr(char *temp)
{
	while (*temp != '.')
		temp++;
	return (ft_strdup(temp));
}

static	char	*getcolor(char *temp)
{
	while (!(ft_isdigit(*temp)))
		temp++;
	return (ft_strdup(temp));
}

void			getinfo(t_mapinfo *s, char *buffer)
{
	char	*temp;
	int		len;

	len = ft_strlen(buffer);
	if ((temp = ft_strchr(buffer, 'R')))
		getres(buffer, s);
	else if (ft_strnstr(buffer, "NO", len))
		s->no = ft_strdup(getstr(buffer));
	else if (ft_strnstr(buffer, "SO", len))
		s->so = ft_strdup(getstr(buffer));
	else if (ft_strnstr(buffer, "WE", len))
		s->we = ft_strdup(getstr(buffer));
	else if (ft_strnstr(buffer, "EA", len))
		s->ea = ft_strdup(getstr(buffer));
	else if (ft_strnstr(buffer, "S .", len))
		s->s = ft_strdup(getstr(buffer));
	else if ((temp = ft_strchr(buffer, 'F')))
		s->f = ft_strdup(getcolor(buffer));
	else if ((temp = ft_strchr(buffer, 'C')))
		s->c = ft_strdup(getcolor(buffer));
	else if ((temp = ft_strchr(buffer, '1')))
		s->map = ft_strjoin(s->map, ft_strjoin(buffer, "\n"));
}
