/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 14:12:39 by marvin            #+#    #+#             */
/*   Updated: 2020/12/03 16:59:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipe_son(int *flag, int *fds, char *str, t_data *param)
{
	int		i;
	char	*command;

	if (!fork())
	{
		if (!flag[0])
			dup2(fds[0], 0);
		if (!flag[1])
			dup2(fds[3], 1);
		i = 0;
		while (i < 4)
			close(fds[i++]);
		command = ft_strldup(str, ft_strlen_pipe(str));
		check_command(command, param);
		exit(param->ret);
	}
}

static int	check_pipe(int *fds, char *str, t_data *param)
{
	int		i;
	int		*flag;

	i = 0;
	flag = (int *)malloc(sizeof(int) * 2);
	flag[0] = 1;
	flag[1] = 0;
	while (!flag[1])
	{
		flag[1] = (!str[ft_strlen_pipe(str)]) ? 1 : 0;
		pipe_son(flag, fds, str, param);
		i++;
		str += ft_strlen_pipe(str) + 1;
		flag[0] = 0;
		close(fds[0]);
		close(fds[1]);
		fds[0] = fds[2];
		fds[1] = fds[3];
		pipe(fds + 2);
	}
	free(flag);
	return (i);
}

static int	change_env(int i, char *cpy, char **str, t_data *param)
{
	int		len;
	char	*bef;
	char	*aft;
	char	*env;
	int		quotes;

	//len = (ft_strlen_char(cpy + i, '"') < ft_strlen_spa(cpy + i)) ?
	//		ft_strlen_char(cpy + i, '"') : ft_strlen_spa(cpy + i);
	quotes = 0;
	if (*(cpy + i) == '"')
	{
		len = ft_strlen_char(cpy + i + 1, '"');
		quotes++;
	}
	else
		len = (ft_strlen_char(cpy + i, ':') < ft_strlen_spa(cpy + i)) ?
		ft_strlen_char(cpy + i, ':') : ft_strlen_spa(cpy + i);
	printf("len = %d\n", len);
	cpy[i] = 0;
	env = (!ft_memcmp(cpy + i + 1, "?", 2) || !ft_memcmp(cpy + i + 1, "? ", 2))
		? ft_itoa(param->ret) : 0;
	bef = ft_strdup(cpy);
	cpy = ft_strldup(cpy + i + 1 + quotes, len - 1);
	printf("cpy = ->%s<-\n", cpy);
	env = (!env) ? ft_strdup(get_env(param->envp, cpy)) : env;
	printf("env = %s\n", env);
	free(cpy);
	cpy = ft_strjoin("\"", env);
	free(env);
	env = ft_strjoin(cpy, "\"");
	free(cpy);
	aft = ft_strdup(*str + i + len + quotes * 2);
	cpy = ft_strjoin(bef, env);
	free(*str);
	*str = ft_strjoin(cpy, aft);
	free(env);
	free(aft);
	free(cpy);
	free(bef);
	cpy = *str;
	return (len + quotes * 2);
}

static void	check_env(char **str, t_data *param)
{
	int i;
	char *cpy;

	cpy = *str;
	i = 0;
	while (cpy && cpy[i])
	{
		if (cpy[i] == '\'')
		{
			i++;
			while (cpy[i] && cpy[i] != '\'')
				i++;
			if (!cpy[i])
			{
				ft_putstr_fd("Non finishedsdf quotes\n", 1);
				break;
			}
			i++;
		}
		if (cpy[i] == '$' || (cpy[i] == '"' && cpy[i + 1] == '$'))
			i += change_env(i, cpy, str, param);
		i++;
	}
}

char		**parser(char *str, t_data *param)
{
	int		fds[4];
	int		std_out;
	int		status;
	int		i;
	int		j;

	if (!str || !ft_memcmp(str, ";", 2))
	{
		if (str)
			ft_putstr_fd("-bash; syntax error near unexpected token `;'\n", 1);
		return (param->envp);
	}
	param->com = ft_split(str, ';');
	j = 0;
	while (param->com[j])
	{
		check_env(&(param->com[j]), param);
		std_out = dup(0);
		//printf("comando = ->%s<-\n", param->com[j]);
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
			//free(param->com[j]);
			while (i < 4)
				close(fds[i++]);
		}
		dup2(std_out, 0);
		j++;
	}
	free(param->str);
	free_env(param->com);
	return (param->envp);
}
