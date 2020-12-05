/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 09:08:52 by jserrano          #+#    #+#             */
/*   Updated: 2020/07/10 10:04:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstsize(t_list *lst)
{
	t_list	*head;
	int		i;

	if (!lst || !(lst->content))
		return (0);
	head = lst;
	i = 0;
	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}
