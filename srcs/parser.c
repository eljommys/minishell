/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 14:12:39 by marvin            #+#    #+#             */
/*   Updated: 2020/12/04 21:13:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	change_env(int i, char **str, t_data *param)
{
	int		len;
	char	*bef;
	char	*aft;
	char	*env;
	char	*aux;

	len = (ft_strlen_char(*str + i + 1, ':') < ft_strlen_spa(*str + i + 1)) ?
	ft_strlen_char(*str + i + 1, ':') + 1 : ft_strlen_spa(*str + i + 1) + 1;
	bef = ft_strldup(*str, i);
	aux = ft_strldup(*str + i + 1, len - 1);
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

static void	check_env(char **str, t_data *param)
{
	int i;

	i = 0;
	while ((*str) && (*str)[i])
	{
		if ((*str)[i] == '\'')
		{
			i++;
			while ((*str)[i] && (*str)[i] != '\'')
				i++;
			if (!(*str)[i])
			{
				ft_putstr_fd("Non finished quotes\n", 1);
				break;
			}
			i++;
		}
		if ((*str)[i] == '$')
			i += change_env(i, str, param) - 1;
		i++;
	}
}

static void command_or_pipe(t_data *param, int j)
{
	int fds[4];
	int std_out;
	int i;

	std_out = dup(0);
	if (param->com[j] && !param->com[j][ft_strlen_pipe(param->com[j])])
		param->envp = check_command(param->com[j], param);
	else if (param->com[j])
	{
		pipe(fds);
		pipe(fds + 2);
		i = check_pipe(fds, param->com[j], param);
		while (i-- > 0)
			wait(&param->ret);
		param->ret /= 256;
		while (i < 4)
			close(fds[i++]);
	}
	dup2(std_out, 0);
}

char		**parser(char *str, t_data *param)
{
	int i;

	if (!str || !ft_memcmp(str, ";", 2))
	{
		if (str)
			ft_putstr_fd("-bash; syntax error near unexpected token `;'\n", 1);
		free(str);
		return (param->envp);
	}
	param->com = ft_split(str, ';');
	i = 0;
	while (param->com[i])
	{
		check_env(&(param->com[i]), param);
		command_or_pipe(param, i);
		i++;
	}
	free(param->str);
	free_env(param->com);
	return (param->envp);
}
