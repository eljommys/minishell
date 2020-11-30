/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 14:12:39 by marvin            #+#    #+#             */
/*   Updated: 2020/11/30 17:54:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strlen_pipe(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '|')
		i++;
	return (i);
}

static void	pipe_son(int *flag, int *fds, char *str, char **envp)
{
	int		i;
	char	*command;
	char	**argv;

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
		check_command(command, argv, envp);
		exit(0);
	}
}

static int	pipes(int *fds, char *str, char **argv, char **envp)
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
		pipe_son(flag, fds, str, envp);
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

char		**check_pipe(char *str, char **argv, char **envp)
{
	int		fds[4];
	int		status;
	int		i;

	if (str && !str[ft_strlen_pipe(str)])
		envp = check_command(str, argv, envp);
	else if (str)
	{
		pipe(fds);
		pipe(fds + 2);
		i = pipes(fds, str, argv, envp);
		while (i-- > 0)
			wait(&status);
		free(str);
		while (i < 4)
			close(fds[i++]);
	}
	return (envp);
}
