/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 12:41:46 by iromero-          #+#    #+#             */
/*   Updated: 2019/11/09 18:45:11 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*str;

	str = (char *)s;
	i = ft_strlen(s);
	if (str[i] == (unsigned char)c)
		return (str + i);
	while (i > 0)
	{
		i--;
		if (str[i] == (unsigned char)c)
			return (str + i);
	}
	return (0);
}
