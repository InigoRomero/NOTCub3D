/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:48:32 by iromero-          #+#    #+#             */
/*   Updated: 2019/11/15 17:12:25 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	num;
	int					neg;

	neg = 1;
	num = 0;
	i = 0;
	while ((str[i] <= 13 && str[i] >= 9) || str[i] == 32)
		i++;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] <= '9' && str[i] >= '0')
	{
		if (num > __LONG_LONG_MAX__ || i >= 19)
		{
			if (neg == 1)
				return (-1);
			else
				return (0);
		}
		num = num * 10 + (str[i++] - 48);
	}
	return ((int)num * neg);
}
