/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:43:44 by iromero-          #+#    #+#             */
/*   Updated: 2019/11/13 19:53:07 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*ft_memcpy(const void *dst, const void *src, size_t n)
{
	unsigned char *strone;
	unsigned char *strtwo;

	strone = (unsigned char *)dst;
	strtwo = (unsigned char *)src;
	if (!n || dst == src)
		return ((char *)dst);
	while (n > 0)
	{
		*strone = *strtwo;
		strone++;
		strtwo++;
		n--;
	}
	return ((char *)dst);
}
