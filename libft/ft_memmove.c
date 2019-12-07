/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 09:17:33 by iromero-          #+#    #+#             */
/*   Updated: 2019/11/13 19:54:02 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*strone;
	unsigned char	*strtwo;
	size_t			i;

	strone = (unsigned char *)dst;
	strtwo = (unsigned char *)src;
	if (src || dst)
	{
		i = 0;
		if (strtwo < strone)
			while (++i <= n)
				strone[n - i] = strtwo[n - i];
		else
			while (n-- > 0)
				*(strone++) = *(strtwo++);
		return (dst);
	}
	else
		return (NULL);
}
