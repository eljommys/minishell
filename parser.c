/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 14:12:39 by marvin            #+#    #+#             */
/*   Updated: 2020/12/01 20:36:32 by marvin           ###   ########.fr       */
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
		exit(0);
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

static int	change_env(int i, char *cpy, char **str, char **envp)
{
	int		len;
	char	*bef;
	char	*aft;
	char	*env;

	len = (ft_strlen_char(cpy + i, '"') < ft_strlen_spa(cpy + i)) ? 
			ft_strlen_char(cpy + i, '"') : ft_strlen_spa(cpy + i);
	cpy[i] = 0;
	bef = ft_strdup(cpy);
	cpy = ft_strldup(cpy + i + 1, len - 1);
	env = ft_strdup(get_env(envp, cpy));
	free(cpy);
	aft = ft_strdup(*str + i + len);
	cpy = ft_strjoin(bef, env);
	free(*str);
	*str = ft_strjoin(cpy, aft);
	free(env);
	free(aft);
	free(cpy);
	free(bef);
	cpy = *str;
}

static void	check_env(char **str, char **envp)
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
				ft_putstr_fd("Non finished quotes\n", 1);
				break;
			}
			i++;
		}
		if (cpy[i] == '$')
			i += change_env(i, cpy, str, envp);
		i++;
	}
}

char		**parser(char *str, t_data *param)
{
	int		fds[4];
	int		std_out;
	int		status;
	int		i;

	check_env(&str, param->envp);
	std_out = dup(0);
	//printf("comando = ->%s<-\n", str);
	if (str && !str[ft_strlen_pipe(str)])
		param->envp = check_command(str, param);
	else if (str)
	{
		pipe(fds);
		pipe(fds + 2);
		i = check_pipe(fds, str, param);
		while (i-- > 0)
			wait(&status);
		free(str);
		while (i < 4)
			close(fds[i++]);
	}
	dup2(std_out, 0);
	return (param->envp);
}
