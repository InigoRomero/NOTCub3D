/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 16:33:18 by iromero-          #+#    #+#             */
/*   Updated: 2019/11/13 19:48:49 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*ft_memchr(const void *ptr, int ch, size_t count)
{
	unsigned char *strone;

	strone = (unsigned char *)ptr;
	while (count--)
	{
		if (*strone == (unsigned char)ch)
			return (strone);
		if (count)
			strone++;
	}
	return (NULL);
}
