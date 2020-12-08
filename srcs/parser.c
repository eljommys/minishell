/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 14:12:39 by marvin            #+#    #+#             */
/*   Updated: 2020/12/09 00:16:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	change_env(int i, int braces, char **str, t_data *param)
{
	int		len;
	char	*bef;
	char	*aft;
	char	*env;
	char	*aux;

	braces = *((*str) + i + 1) == '{' ? 1 : 0;
	len = (ft_strlen_char(*str + i + 1, ':') < ft_strlen_token(*str + i + 1)) ?
	ft_strlen_char(*str + i + 1, ':') + 1 : ft_strlen_token(*str + i + 1) + 1;
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

static int	check_env(char **str, t_data *param)
{
	int		i;
	int		braces;
	char	*aux;
	char	*bef;

	i = 0;
	braces = 0;
	while ((*str) && (*str)[i])
	{
		if ((*str)[i] == '\'')
		{
			i++;
			while ((*str)[i] && ((*str)[i] != '\''))
			{
				if ((*str)[i] == '\\')
					i++;
				i++;
			}
			if (!(*str)[i])
			{
				ft_putstr_fd("Non finished quotes\n", 1);
				return (1);
			}
		}
		if ((*str)[i] && (*str)[i] == '\\' && (*str)[i] == '$')
		{
			bef = ft_strldup(*str, i);
			aux = ft_strdup(*str + i + 1);
			free(*str);
			*str = ft_strjoin(bef, aux);
			free(aux);
			free(bef);
			i++;
		}
		else  if ((*str)[i] == '$')
			i += change_env(i, braces, str, param) - 1;
		i++;
	}
	return (0);
}

static void	command_or_pipe(t_data *param, int j)
{
	int fds[4];
	int std_out;
	int sons;
	int i;

	std_out = dup(0);
	if (param->cmds[j] && !param->cmds[j][ft_strlen_pipe(param->cmds[j])])
		param->envp = check_command(param->cmds[j], param);
	else if (param->cmds[j])
	{
		pipe(fds);
		pipe(fds + 2);
		sons = check_pipe(fds, param->cmds[j], param);
		while (sons-- > 0)
			wait(&param->ret);
		param->ret /= 256;
		i = -1;
		while (++i < 4)
			close(fds[i]);
	}
	dup2(std_out, 0);
}

void		parser(t_data *param)
{
	int		i;

	if (!param->str || !ft_memcmp(param->str, ";", 2))
	{
		if (param->str)
		{
			ft_putstr_fd("-bash; syntax error near unexpected token `;'\n", 1);
			param->ret = 2;
		}
		free(param->str);
		return ;
	}
	param->cmds = ft_split_case(param->str, ';');
	i = 0;
	while (param->cmds[i])
	{
		if (check_env(&(param->cmds[i]), param))
			break ;
		command_or_pipe(param, i);
		i++;
	}
	free(param->str);
	free_matrix(param->cmds);
}
