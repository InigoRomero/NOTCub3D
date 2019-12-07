/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 18:54:28 by iromero-          #+#    #+#             */
/*   Updated: 2019/11/12 19:36:31 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*s;
	size_t	i;

	i = 0;
	if (count < 0 || size < 0)
		return (NULL);
	if (!(s = malloc(count * size)))
		return (NULL);
	while (i < count * size)
	{
		((char *)s)[i] = '\0';
		i++;
	}
	return (s);
}
