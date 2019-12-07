/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 09:30:24 by iromero-          #+#    #+#             */
/*   Updated: 2019/11/14 19:19:18 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstnew(void const *content)
{
	t_list *x;

	if (!(x = malloc(sizeof(t_list))))
		return (NULL);
	x->content = (void *)content;
	x->next = NULL;
	return (x);
}
