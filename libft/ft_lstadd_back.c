/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 12:02:45 by jserrano          #+#    #+#             */
/*   Updated: 2020/07/11 10:51:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *head;

	if (!alst || !new)
		return ;
	if (*alst)
	{
		head = *alst;
		while (head->next)
			head = head->next;
		head->next = new;
	}
	else
		*alst = new;
}
