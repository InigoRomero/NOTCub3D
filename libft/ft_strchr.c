/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 12:36:09 by iromero-          #+#    #+#             */
/*   Updated: 2019/11/10 17:39:12 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int i;
	unsigned int len;

	i = 0;
	len = ft_strlen(s);
	while (*s && *s != c)
	{
		i++;
		s++;
	}
	if (len == i && *s != c)
		return (NULL);
	return ((char *)s);
}
