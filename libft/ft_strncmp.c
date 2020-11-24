/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 09:04:14 by jserrano          #+#    #+#             */
/*   Updated: 2020/07/10 10:09:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char *c1;
	unsigned char *c2;

	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;
	while (0 < n--)
	{
		if (*(c1++) != *(c2++))
			return (*(--c1) - *(--c2));
		else if (!(*c1) || !(*c2))
			return (*(c1) - *(c2));
	}
	return (0);
}
