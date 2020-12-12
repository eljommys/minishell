/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lens.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 19:09:39 by marvin            #+#    #+#             */
/*   Updated: 2020/12/12 00:50:25 by marvin           ###   ########.fr       */
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
				if (str[i] == '\\' && is_token(str[i + 1]))
					i++;
				i++;
			}
			if (!str[i])
			{
				ft_putstr_fd("Non finished quotes(lens)\n", 1);
				return (i);
			}
		}
		else if (str[i] == '\\')
			i++;
		i++;
	}
	return (i);
}

int		ft_strlen_char_token(char *str, char c)
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
	while (*str && (ft_isalnum(*str) || *str == '{'))
	{
		len++;
		str++;
	}
	if (*str == '=')
		len++;
	return (len);
}
