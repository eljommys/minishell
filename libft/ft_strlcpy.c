/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 09:02:45 by jserrano          #+#    #+#             */
/*   Updated: 2020/07/08 10:49:19 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	length_src;
	size_t	i;

	if (!dest || !src)
		return (0);
	length_src = 0;
	while (src[length_src])
		length_src++;
	if (n)
	{
		i = -1;
		if (length_src + 1 < n)
			while (++i < length_src)
				dest[i] = src[i];
		else
			while (++i < n - 1)
				dest[i] = src[i];
		dest[i] = '\0';
	}
	return (length_src);
}
