/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 09:07:09 by jserrano          #+#    #+#             */
/*   Updated: 2020/07/10 09:40:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *aux;

	if (!lst || !(*lst) || !del)
		return ;
	while ((*lst))
	{
		aux = *lst;
		del((*lst)->content);
		(*lst) = (*lst)->next;
		free(aux);
	}
}
