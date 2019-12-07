/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 09:33:13 by iromero-          #+#    #+#             */
/*   Updated: 2019/11/14 18:52:27 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

static size_t	end(char const *s1, char const *set, size_t i)
{
	size_t n;
	size_t sum;
	size_t leng;

	leng = 0;
	i = ft_strlen(s1) - 1;
	while (i > 0)
	{
		n = 0;
		sum = leng;
		while (n < ft_strlen(set))
		{
			if (s1[i] == set[n++])
				leng++;
		}
		if (sum == leng)
			break ;
		i--;
	}
	return (leng);
}

static size_t	countofchars(char const *s1, char const *set, size_t i)
{
	size_t n;
	size_t sum;
	size_t leng;

	leng = 0;
	while (i < ft_strlen(s1) - 1)
	{
		n = 0;
		sum = leng;
		while (n < ft_strlen(set))
		{
			if (s1[i] == set[n++])
				leng++;
		}
		if (sum == leng)
			break ;
		i++;
	}
	i = 0;
	return (leng);
}

static char		*fillchar(char const *s1, char *dest, size_t start, size_t end)
{
	size_t i;

	i = 0;
	while (start < (ft_strlen(s1) - end))
		dest[i++] = s1[start++];
	dest[i] = '\0';
	return (dest);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char	*dest;
	size_t	i;
	size_t	leng;

	i = 0;
	if (!s1)
		return (NULL);
	leng = countofchars(s1, set, i) + end(s1, set, i);
	if (leng >= ft_strlen(s1))
		return (ft_strdup(""));
	if (!(dest = (char*)malloc((ft_strlen(s1) - leng + 1))))
		return (NULL);
	return (fillchar(s1, dest, countofchars(s1, set, i), end(s1, set, i)));
}
