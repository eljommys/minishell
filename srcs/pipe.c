/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 16:11:27 by marvin            #+#    #+#             */
/*   Updated: 2020/12/06 11:19:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipe_son(int *flag, int *fds, char *str, t_data *param)
{
	int		i;
	char	*command;

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
		command = ft_strldup(str, ft_strlen_pipe(str));
		check_command(command, param);
		exit(param->ret);
	}
}

int			check_pipe(int *fds, char *str, t_data *param)
{
	int		sons;
	int		*flag;

	sons = 0;
	flag = (int *)malloc(sizeof(int) * 2);
	flag[0] = 1;
	flag[1] = 0;
	while (!flag[1])
	{
		flag[1] = (!str[ft_strlen_pipe(str)]) ? 1 : 0;
		pipe_son(flag, fds, str, param);
		sons++;
		str += ft_strlen_pipe(str) + 1;
		flag[0] = 0;
		close(fds[0]);
		close(fds[1]);
		fds[0] = fds[2];
		fds[1] = fds[3];
		pipe(fds + 2);
	}
	free(flag);
	return (sons);
}
