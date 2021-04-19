/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getinfo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 20:51:50 by iromero-          #+#    #+#             */
/*   Updated: 2021/04/19 17:04:34 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

static	void	getres(char *temp, t_mapinfo *s)
{
	int		i;
	int		aux;
	char	*temp2;

	i = 0;
	while (!(ft_isdigit(temp[i])))
		i++;
	aux = i;
	while (ft_isdigit(temp[i]))
		i++;
	temp2 = ft_substr(temp, aux, i);
	s->x = ft_atoi(temp2);
	free(temp2);
	while (temp[i] == ' ')
		i++;
	aux = i;
	while (ft_isdigit(temp[i]))
		i++;
	temp2 = ft_substr(temp, aux, i);
	s->y = ft_atoi(temp2);
	free(temp2);
}

static	char	*getstr(char *temp)
{
	while (*temp != '.')
		temp++;
	return (temp);
}

static	char	*getcolor(char *temp)
{
	while (!(ft_isdigit(*temp)))
		temp++;
	return (temp);
}

void			takeline(t_mapinfo *s, char *temp, char *buffer)
{
	char *temp2;

	temp = ft_strjoin(buffer, "\n");
	temp2 = s->map;
	s->map = ft_strjoin(s->map, temp);
	free(temp2);
	free(temp);
}

void			getinfo(t_mapinfo *s, char *buffer)
{
	char	*temp;
	int		len;

	len = ft_strlen(buffer);
	if ((temp = ft_strchr(buffer, 'R')))
		getres(buffer, s);
	else if ((temp = ft_strnstr(buffer, "NO", len)))
		s->no = ft_strdup(getstr(buffer));
	else if ((temp = ft_strnstr(buffer, "SO", len)))
		s->so = ft_strdup(getstr(buffer));
	else if ((temp = ft_strnstr(buffer, "WE", len)))
		s->we = ft_strdup(getstr(buffer));
	else if ((temp = ft_strnstr(buffer, "EA", len)))
		s->ea = ft_strdup(getstr(buffer));
	else if ((temp = ft_strnstr(buffer, "S .", len)))
		s->s = getstr(buffer);
	else if ((temp = ft_strchr(buffer, 'F')))
		s->f = getcolor(buffer);
	else if ((temp = ft_strchr(buffer, 'C')))
		s->c = getcolor(buffer);
	else if ((temp = ft_strchr(buffer, '1')))
		takeline(s, temp, buffer);
}
