/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:04:27 by iromero-          #+#    #+#             */
/*   Updated: 2019/11/13 18:33:14 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	size_t i;

	i = 0;
	if (!lst)
		return ;
	while (lst->next != NULL)
	{
		i++;
		f(lst->content);
		lst = lst->next;
	}
	f(lst->content);
}
