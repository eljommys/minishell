/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 08:34:36 by jserrano          #+#    #+#             */
/*   Updated: 2020/07/11 10:50:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	result_neg_i
*/

int		ft_atoi(const char *str)
{
	long long int	var[3];

	var[0] = 0;
	var[1] = 1;
	var[2] = 0;
	while (str[var[2]] == 32 || (9 <= str[var[2]] && str[var[2]] <= 13))
		var[2]++;
	if (str[var[2]] == '-' || str[var[2]] == '+')
		var[1] = (str[var[2]++] == '-') ? -1 : 1;
	while (str[var[2]])
	{
		if (str[var[2]] < 48 || 57 < str[var[2]])
			return (var[0] * var[1]);
		else
			var[0] = (var[0] * 10) + (long long int)(str[var[2]] - '0');
		if (var[0] < -2147483648)
			return (1);
		else if (2147483648 < var[0])
			return (0);
		var[2]++;
	}
	return ((long int)(var[0] * var[1]));
}
