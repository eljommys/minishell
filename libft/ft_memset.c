/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 11:58:30 by jserrano          #+#    #+#             */
/*   Updated: 2020/07/10 10:07:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char *ptr;

	ptr = (unsigned char *)str;
	while (0 < n--)
		*(ptr++) = (unsigned char)c;
	return (str);
}
