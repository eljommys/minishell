/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 08:54:38 by jserrano          #+#    #+#             */
/*   Updated: 2020/11/30 22:35:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"



char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		len;
	char	*str;

	if (s1 && s2)
		{
			len = ft_strlen(s1);
			if (!(str = (char*)malloc(1 * (len + ft_strlen(s2) + 1))))
				return (NULL);
			i = -1;
			while (s1[++i])
				str[i] = s1[i];
			i = -1;
			while (s2[++i])
			{
				str[len] = s2[i];
				len++;
			}
			str[len] = '\0';
			return (str);
		}
	else if (s1)
		return (ft_strdup(s1));
	return (NULL);
}
