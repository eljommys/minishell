/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paris <paris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 09:02:17 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/25 10:22:26 by paris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t len;
	size_t len1;
	size_t i;

	len = ft_strlen(src);
	len1 = ft_strlen(dst);
	i = 0;
	if (size <= len1)
		return (len + size);
	else
		len += len1;
	while (src[i] != 0 && len1 + 1 < size)
	{
		dst[len1] = src[i];
		len1++;
		i++;
	}
	dst[len1] = 0;
	return (len);
}

