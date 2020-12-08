/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 17:29:24 by marvin            #+#    #+#             */
/*   Updated: 2020/12/08 22:30:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strlen_arg(char *str)
{
	int		i;

	i = 0;
	if (*str == '"' || *str == '\'')
		i = ft_strlen_char(str + 1, *str) + 2;
	else if (ft_strlen_char(str, ':') < ft_strlen_token(str))
		i = ft_strlen(str);
	else
		i = ft_strlen_token(str);
	if (*str == '>')
		i = (*(str + 1) == '>') ? 2 : 1;
	else if (*str == '<')
		i = 1;
	else
		i = (ft_strlen_char(str, '<') < i) ? ft_strlen_char(str, '<') : i;
	return (i);
}

int			count_args(char *str)
{
	int		i;

	i = 0;
	while (*str)
	{
		skip_spaces(&str);
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
		argv[i] = ft_strldup(str + quotes, len - quotes * 2);
		str += len;
		i++;
	}
}

char		**copy_args(t_data *param)
{
	int		i;
	char	**args;

	i = 0;
	while (param->argv[i] && ft_memcmp(param->argv[i], "<", 2))
		i++;
	args = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	while (param->argv[i] && ft_memcmp(param->argv[i], "<", 2))
	{
		args[i] = ft_strdup(param->argv[i]);
		i++;
	}
	return (args);
}
