/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lens.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 19:09:39 by marvin            #+#    #+#             */
/*   Updated: 2020/12/13 13:46:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_strlen_pipe(char *str)
{
	int		i;
	char	c;

	i = -1;
	while (str[++i] && str[i] != '|')
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			c = str[i++];
			while (str[i] && str[i] != c)
			{
				if (str[i] == '\\' && is_token(str[i + 1]))
					i++;
				i++;
			}
			if (!str[i])
			{
				ft_putstr_fd("Non finished quotes\n", 2);
				return (i);
			}
		}
		else if (str[i] == '\\')
			i++;
	}
	return (i);
}

int		ft_strlen_arg_token(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] && str[i] != c)
	{
		if (str[i] == '\\' && is_token(str[i + 1]))
			i++;
		i++;
	}
	return (i);
}

int		ft_strlen_char(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
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

int		ft_strlen_env(char *str)
{
	int		len;

	len = 0;
	while (*str && (ft_isalnum(*str) || *str == '{' || *str == '?' || *str == '_' ))
	{
		len++;
		str++;
	}
	if (*str == '=')
		len++;
	return (len);
}
