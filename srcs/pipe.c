/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 16:11:27 by marvin            #+#    #+#             */
/*   Updated: 2020/12/12 12:31:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_pipe_args(t_data *param, int i)
{
	char	**aux;
	int		j;
	int		k;

	j = 0;
	while (param->argv[i + j] && ft_memcmp(param->argv[i + j] , "|", 2))
		j++;
	aux = (char **)ft_calloc(sizeof(char *), j + 1);
	k = -1;
	while (++k < j)
		aux[k] = ft_strdup(param->argv[i]);
	param->argv = aux;
	param->argc = j;
}

static void	pipe_son(int *flag, int *fds, char *str, t_data *param, int pos)
{
	int		i;
	char	*command;
	int		argc;
	char	**argv;

	signal(SIGINT, child_sig_handler);
	if (!fork())
	{
		if (!flag[0])
			dup2(fds[0], 0);
		if (!flag[1])
			dup2(fds[3], 1);
		i = 0;
		while (i < 4)
			close(fds[i++]);
		argc = param->argc;
		argv = param->argv;
		//command = ft_strldup(str, ft_strlen_pipe(str));
		//check_command(command, param);
		set_pipe_args(param, pos);
		check_command(param->str, param);
		param->argc = argc;
		param->argv = argv;
		exit(param->ret);
	}
}

int			check_pipe(int *fds, char *str, t_data *param)
{
	int		sons;
	int		*flag;
	int		i;
	int		j;

	sons = 0;
	flag = (int *)malloc(sizeof(int) * 2);
	flag[0] = 1;
	flag[1] = 0;
	j = 0;
	while (!flag[1])
	{
		i = 0;
		while (param->argv[j + i] && ft_memcmp(param->argv[j + i], "|", 2))
			i++;
		//flag[1] = (!str[ft_strlen_pipe(str)]) ? 1 : 0;
		flag[1] = (!param->argv[i + j]) ? 1 : 0;
		pipe_son(flag, fds, str, param, j);
		sons++;
		//str += ft_strlen_pipe(str) + 1;
		flag[0] = 0;
		close(fds[0]);
		close(fds[1]);
		fds[0] = fds[2];
		fds[1] = fds[3];
		pipe(fds + 2);
		j += i;
	}
	free(flag);
	return (sons);
}
