/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 12:52:04 by iromero-          #+#    #+#             */
/*   Updated: 2019/11/13 15:14:30 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include <stdio.h>

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *pop;

	if (lst)
	{
		while (*lst)
		{
			pop = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = pop;
		}
	}
}
