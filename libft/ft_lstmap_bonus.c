/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:31:26 by iromero-          #+#    #+#             */
/*   Updated: 2019/11/15 10:27:33 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list		*current;
	t_list		*head;
	t_list		*aux;

	if (!lst)
		return (NULL);
	current = ft_lstnew(f(lst->content));
	head = current;
	lst = lst->next;
	while (lst)
	{
		aux = lst->next;
		if (!(current->next = ft_lstnew(f(lst->content))))
			del(lst);
		current = current->next;
		lst = aux;
	}
	return (head);
}
