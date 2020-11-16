/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 09:08:30 by jserrano          #+#    #+#             */
/*   Updated: 2020/07/07 12:31:21 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*last;

	if (!lst || !(lst->content))
		return (NULL);
	head = ft_lstnew(f(lst->content));
	last = head;
	while (lst->next)
	{
		lst = lst->next;
		if (!(last->next = ft_lstnew(f(lst->content))))
		{
			while (head)
			{
				del(head->content);
				head = head->next;
			}
			return (NULL);
		}
		last = last->next;
		last->content = f(lst->content);
	}
	return (head);
}
