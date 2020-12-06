/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 00:01:09 by marvin            #+#    #+#             */
/*   Updated: 2020/12/06 10:17:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		exit_command(t_data *param)
{
	free(param->str);
	free_matrix(param->envp);
	free_matrix(param->argv);
	free_matrix(param->cmds);
	free(param);
	exit(0);
}

static void	pwd_command(int fd)
{
	char *cwd;
	char buff[4097];

	cwd = getcwd(buff, 4096);
	ft_putstr_fd(cwd, fd);
	write(fd, "\n", 1);
}

static void	echo_command(t_data *param, int fd)
{
	int i;

	i = (param->argc > 1 && !ft_memcmp(param->argv[1], "-n", 3))
	? 1 : 0;
	while (++i < param->argc)
	{
		ft_putstr_fd(param->argv[i], fd);
		if (i < param->argc - 1)
			write(1, " ", 1);
	}
	if (param->argc > 1 && ft_memcmp(param->argv[1], "-n", 3))
		write(fd, "\n", 1);
	if (fd != 1)
		close(fd);
}

int			check_builtins(int fd, t_data *param)
{
	if (!ft_memcmp(param->argv[0], "echo", 5))
		echo_command(param, fd);
	else if (!ft_memcmp(param->argv[0], "pwd", 4))
		pwd_command(fd);
	else if (!ft_memcmp(param->argv[0], "cd", 3))
		cd_command(param);
	else if (!ft_memcmp(param->argv[0], "env", 4))
		env_command(param, fd);
	else if (!ft_memcmp(param->argv[0], "./", 2) ||
			!ft_memcmp(param->argv[0], "../", 3) ||
			!ft_memcmp(param->argv[0], "/", 1))
		bash_command(param);
	else if (!ft_memcmp(param->argv[0], "export", 7))
		param->envp = export_command(param);
	else if (!ft_memcmp(param->argv[0], "unset", 6))
		param->envp = unset_command(param);
	else if (!ft_memcmp(param->argv[0], "exit", 5) ||
			!ft_memcmp(param->argv[0], "q", 2))
		exit_command(param);
	else
		return (1);
	return (0);
}
