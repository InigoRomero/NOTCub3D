/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 11:38:54 by iromero-          #+#    #+#             */
/*   Updated: 2019/11/10 18:59:16 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*strone;

	strone = (unsigned char *)b;
	while (len > 0)
	{
		*strone = (unsigned char)c;
		strone++;
		len--;
	}
	return (b);
}
