/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 14:12:39 by marvin            #+#    #+#             */
/*   Updated: 2020/12/13 13:24:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int change_env(int i, int braces, char **str, t_data *param)
{
	int len;
	char *bef;
	char *aft;
	char *env;
	char *aux;

	braces = ((*str)[i + 1] == '{') ? 1 : 0;
	len = (ft_strlen_char(*str + i + 1, ':') < ft_strlen_env(*str + i + 1)) ? ft_strlen_char(*str + i + 1, ':') + 1 : ft_strlen_env(*str + i + 1) + 1 + braces;
	bef = ft_strldup(*str, i);
	aux = ft_strldup(*str + i + 1 + braces, len - 1 - braces * 2);
	env = (!ft_memcmp(aux, "?", 2)) ? ft_itoa(param->ret) : 0;
	aft = ft_strdup(*str + i + len);
	env = (!env) ? ft_strdup(get_env(param->envp, aux)) : env;
	free(aux);
	len = ft_strlen(env);
	aux = ft_strjoin(bef, env);
	free(bef);
	free(env);
	free(*str);
	*str = ft_strjoin(aux, aft);
	free(aux);
	free(aft);
	return (len);
}

static int check_quotes(char **str, int *i)
{
	(*i)++;
	while ((*str)[*i] && ((*str)[*i] != '\''))
		(*i)++;
	if (!(*str)[*i])
	{
		ft_putstr_fd("Non finished quotes(parser)\n", 1);
		return (1);
	}
	return (0);
}

static int check_env(char **str, t_data *param)
{
	int i;
	int braces;

	i = 0;
	braces = 0;
	while ((*str) && (*str)[i])
	{
		if ((*str)[i] == '\'' && check_quotes(str, &i))
			return (1);
		if ((*str)[i] && (*str)[i] == '\\')
		{
			if ((*str)[i + 1] == '$')
				rm_char(str, i);
			if ((*str)[i + 1])
				i++;
		}
		else if ((*str)[i] == '$' && !(!(*str)[i + 1] ||
		ft_isspace((*str)[i + 1]) || (*str)[i + 1] == '\'' ||
		(*str)[i + 1] == '"' || (*str)[i + 1] == '/'))
			i += change_env(i, braces, str, param) - 1;
		i++;
	}
	return (0);
}

static int	check_semicolon(t_data *param)
{
	if (!param->str || !ft_memcmp(param->str, ";", 2))
	{
		if (param->str)
		{
			ft_putstr_fd("-bash; syntax error near unexpected token `;'\n", 1);
			param->ret = 2;
		}
		free(param->str);
		param->str = 0;
		return (1);
	}
	return (0);
}

void		parser(t_data *param)
{
	int i;

	if (check_semicolon(param))
		return ;
	param->cmds = ft_split_case(param->str, ';');
	i = 0;
	while (param->cmds[i])
	{
		check_env(&(param->cmds[i]), param);
		param->argc = count_args(param->cmds[i]);
		param->argv = (char **)ft_calloc(sizeof(char *), (param->argc + 1));
		set_args(param->argv, param->cmds[i], param->argc);
		command_or_pipe(param, i);
		i++;
		free_matrix(param->argv);
	}
	free(param->str);
	param->str = 0;
	free_matrix(param->cmds);
}
