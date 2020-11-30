/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 17:29:24 by marvin            #+#    #+#             */
/*   Updated: 2020/11/30 17:29:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			count_args(char *str)
{
	int		i;

	i = 0;
	while (*str && *str != '|' && *str != '<' && *str != '&' && *str != '>' &&
		*str != ';')
	{
		skip_spaces(&str);
		i++;
		str += ft_strlen_spa(str);
	}
	return (i);
}

static int	ft_strlen_quote(char *str)
{
	int		i;
	char	quote;

	quote = *str;
	str++;
	i = 0;
	while (str[i] && str[i] != quote)
		i++;
	return (i);
}

void		set_args(char **argv, char *str, int argc)
{
	int i;
	int len;

	i = 0;
	while (i < argc)
	{
		skip_spaces(&str);
		len = ft_strlen_spa(str);
		if (len)
		{
			if (*str == '"' || *str == '\'')
			{
				len = ft_strlen_quote(str);
				str++;
			}
			argv[i] = ft_strldup(str, len);
			str++;
		}
		str += len;
		i++;
	}
}