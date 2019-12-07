/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:30:40 by iromero-          #+#    #+#             */
/*   Updated: 2019/11/13 19:47:48 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char *strone;
	unsigned char *strtwo;

	strone = (unsigned char *)dst;
	strtwo = (unsigned char *)src;
	while (n > 0)
	{
		*strone = *strtwo;
		strone++;
		if (*strtwo++ == (unsigned char)c)
			return (strone);
		n--;
	}
	return (NULL);
}
