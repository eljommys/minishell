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

	i = 0;
	quote = 0;
	if (str[i] == '"' || str[i] == '\'')
		i = ft_strlen_char(str + i + 1, str[i]) + 2;
	else if (ft_strlen_char(str, ':')  < ft_strlen_spa(str))
		i = ft_strlen(str);
	else
		i = ft_strlen_spa(str);
	return (i);
}

int			count_args(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (*str && *str != '|' && *str != '&' && *str != '>' &&
		*str != ';')
	{
		skip_spaces(&str);
		c = (*str == '"' || *str == '\'') ? 2 : 0;
		str += ft_strlen_arg(str);
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
		len = ft_strlen_arg(str);
		quotes = (*str == '"' || *str == '\'') ? 1 : 0;
		argv[i] = ft_strldup(str + quotes , len - quotes * 2);
		str += len;
		i++;
	}
}
