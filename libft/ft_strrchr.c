/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 09:14:28 by jserrano          #+#    #+#             */
/*   Updated: 2020/07/10 10:08:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*s1;
	int		len;

	s1 = (char *)s;
	len = 0;
	while (s1[len])
		len++;
	while (s1[len] != c && len != 0)
		len--;
	if (s1[len] == c)
		return (&s1[len]);
	else
		return (NULL);
}
