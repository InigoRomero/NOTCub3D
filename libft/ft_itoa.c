/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:15:22 by iromero-          #+#    #+#             */
/*   Updated: 2019/11/14 18:53:52 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include <stdlib.h>

static int		longofnum(long int n)
{
	int leng;

	leng = 0;
	if (n < 0)
	{
		leng++;
		n = n * -1;
	}
	while (n > 0)
	{
		n = n / 10;
		leng++;
	}
	return (leng);
}

static char		*inttochar(long int n, char *num, int leng)
{
	num[leng--] = '\0';
	if (n == 0)
		num[0] = 48;
	if (n < 0)
	{
		num[0] = '-';
		n = n * -1;
	}
	while (n > 0)
	{
		num[leng--] = 48 + (n % 10);
		n = n / 10;
	}
	return (num);
}

char			*ft_itoa(int n)
{
	char	*num;
	int		leng;

	leng = longofnum((long int)n);
	if (!n)
		leng = 1;
	if (!(num = (char *)malloc(sizeof(char) * (leng + 1))))
		return (NULL);
	return (num = inttochar((long int)n, num, leng));
}
