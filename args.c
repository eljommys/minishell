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

static int	ft_strlen_arg(char *str)
{
	int		i;
	char	quote;

	/*quote = *str;
	str++;
	i = 0;
	while (str[i] && str[i] != quote)
		i++;
	return (i);*/
	i = 0;
	quote = 0;
	if (str[i] == '"' || str[i] == '\'')
	{
		quote = str[i];
		i++;
		while (str[i] != quote)
			i++;
		i++;
	}
	else
		i = ft_strlen_spa(str);
	i = (quote) ? i - 2 : i;
	return (i);
}

int			count_args(char *str)
{
	int		i;
	char	c;
	int		j;

	i = 0;
	while (*str && *str != '|' && *str != '&' && *str != '>' &&
		*str != ';')
	{
		skip_spaces(&str);
		/*if (*str == '"' || *str == '\'')
		{
			c = *str;
			str++;
			while (*str != c)
				str++;
			str++;
		}
		else
			str += ft_strlen_spa(str);*/
		j = (*str == '"' || *str == '\'') ? 2 : 0;
		str += ft_strlen_arg(str) + j;
		i++;
		skip_spaces(&str);
	}
	return (i);
}

void		set_args(char **argv, char *str, int argc)
{
	int i;
	int len;
	int quotes;

	i = 0;
	while (i < argc)
	{
		skip_spaces(&str);
		/*len = ft_strlen_spa(str);
		if (len)
		{
			if (*str == '"' || *str == '\'')
			{
				len = ft_strlen_arg(str);
				str++;
			}
			argv[i] = ft_strldup(str, len);
			str++;
		}
		str += len;
		i++;*/
		len = ft_strlen_arg(str);
		quotes = (*str == '"' || *str == '\'') ? 1 : 0;
		argv[i] = ft_strldup(str + quotes, len);
		str += len + quotes * 2;
		i++;
	}
}
