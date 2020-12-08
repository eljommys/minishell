/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 00:01:09 by marvin            #+#    #+#             */
/*   Updated: 2020/12/08 17:56:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		exit_command(t_data *param)
{
	free(param->str);
	free_matrix(param->envp);
	free_matrix(param->export);
	free_matrix(param->argv);
	free_matrix(param->cmds);
	free(param);
	exit(0);
}

static void env_command(t_data *param, int fd)
{
	int i;

	i = 0;
	if (param->argc != 1)
	{
		ft_putstrs_fd("env: ‘", param->argv[1], "’: Permission denied\n", 1);
		return;
	}
	while (param->envp[i])
		ft_putstrs_fd(param->envp[i++], "\n", 0, fd);
}

static void	pwd_command(int fd)
{
	char cwd[4097];

	getcwd(cwd, 4096);
	ft_putstrs_fd(cwd, "\n", 0, fd);
}

static void	echo_command(t_data *param, int fd)
{
	int i;

	i = (param->argc > 1 && !ft_memcmp(param->argv[1], "-n", 3)) ? 1 : 0;
	while (++i < param->argc)
	{
		ft_putstr_fd(param->argv[i], fd);
		if (i < param->argc - 1)
			write(fd, " ", 1);
	}
	if (param->argc > 1 && ft_memcmp(param->argv[1], "-n", 3))
		write(fd, "\n", 1);
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
	else if (!ft_memcmp(param->argv[0], "export", 7) ||
			!ft_memcmp(param->argv[0], "unset", 6))
		param->envp = multiple_env(param, fd);
	else if (!ft_memcmp(param->argv[0], "exit", 5) ||
			!ft_memcmp(param->argv[0], "q", 2))
		exit_command(param);
	else
		return (1);
	return (0);
}
