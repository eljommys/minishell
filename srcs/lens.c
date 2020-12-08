/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lens.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 19:09:39 by marvin            #+#    #+#             */
/*   Updated: 2020/12/09 00:11:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_strlen_pipe(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i] && str[i] != '|')
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			c = str[i];
			i++;
			while (str[i] && str[i] != c)
			{
				if (str[i] == '\\')
					i++;
				i++;
			}
			if (!str[i])
			{
				ft_putstr_fd("Non finished quotes\n", 1);
				return (1);
			}
		}
		i++;
	}
	return (i);
}

int		ft_strlen_char(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] && str[i] != c)
	{
		if (str[i] == '\\')
			i++;
		i++;
	}
	return (i);
}

int		ft_strlen_token(char *str)
{
	int		len;

	len = 0;
	while (*str && *str != ' ' && *str != ';' && *str != '|' && *str != '<'
	&& *str != '>' && *str != '"' && *str != '\'' && *str != '=')
	{
		len++;
		str++;
	}
	if (*str == '=')
		len++;
	return (len);
}
