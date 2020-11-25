/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paris <paris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 09:01:23 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/25 10:23:09 by paris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(char *s)
{
	char	*ptr;
	int		size;
	int		i;

	size = 0;
	while (s[size])
		size++;
	if (!(ptr = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	i = 0;
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
