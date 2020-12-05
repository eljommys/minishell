/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jserrano <jserrano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 08:55:12 by jserrano          #+#    #+#             */
/*   Updated: 2020/07/08 13:30:25 by jserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*res;
	int		len;
	int		i;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	if (!(res = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	i = -1;
	while (s[++i])
		res[i] = f(i, s[i]);
	res[i] = 0;
	return (res);
}
