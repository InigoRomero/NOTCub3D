/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 11:39:37 by iromero-          #+#    #+#             */
/*   Updated: 2019/12/03 11:04:18 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *current;

	current = (*alst);
	if (current == NULL)
		(*alst) = new;
	else
	{
		current = ft_lstlast(*alst);
		current->next = new;
	}
}
