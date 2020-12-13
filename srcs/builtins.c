/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 00:01:09 by marvin            #+#    #+#             */
/*   Updated: 2020/12/13 13:30:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**multiple_env(t_data *param, int fd)
{
	int i;

	param->ret = 0;
	if (!ft_memcmp(param->argv[0], "export", 7) && param->argc == 1 &&
		!ft_strlen(param->argv[1]))
	{
		sort_envp(param->envp, fd, '=');
		sort_envp(param->export, fd, 0);
	}
	i = 1;
	while (param->argv[i])
	{
		if (check_export_error(param->argv, &i))
			(param->ret)++;
		else
		{
			if (!ft_memcmp(param->argv[0], "export", 7))
				export_value(param, &i);
			else if (!ft_memcmp(param->argv[0], "unset", 6))
				param->envp = unset_command(param, i++);
		}
	}
	param->ret = param->ret ? 1 : 0;
	return (param->envp);
}

static void	env_command(t_data *param, int fd)
{
	int i;

	i = 0;
	if (param->argc != 1)
	{
		ft_putstrs_fd("env: ‘", param->argv[1], "’: Permission denied\n", 2);
		param->ret = 126;
		return ;
	}
	while (param->envp[i])
		ft_putstrs_fd(param->envp[i++], "\n", 0, fd);
}

static void	echo_command(t_data *param, int fd)
{
	int i;

	i = (param->argc > 1 && !ft_memcmp(param->argv[1], "-n", 3)) ? 1 : 0;
	while (++i < param->argc)
	{
		ft_putstr_fd(param->argv[i], fd);
		if (i < param->argc - 1 && ft_strlen(param->argv[i + 1]))
			write(fd, " ", 1);
	}
	if (!(param->argc > 1 && !ft_memcmp(param->argv[1], "-n", 3)))
		write(fd, "\n", 1);
}

static int	check_builts(int fd, t_data *param)
{
	char *path;
	char cwd[4097];

	path = 0;
	if (!ft_memcmp(param->argv[0], "echo", 5))
		echo_command(param, fd);
	else if (!ft_memcmp(param->argv[0], "pwd", 4))
		ft_putstrs_fd(getcwd(cwd, 4096), "\n", 0, fd);
	else if (!ft_memcmp(param->argv[0], "cd", 3))
	{
		path = ft_strdup(param->argv[1]);
		cd_command(param);
		if (path && !ft_strncmp(path, "-", 2))
			ft_putstrs_fd(getcwd(cwd, 4096), "\n", 0, fd);
		free(path);
	}
	else
		return (1);
	return (0);
}

int			check_builtins(int fd, t_data *param)
{
	param->ret = 0;
	if (!check_builts(fd, param))
		return (param->ret);
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
		return (127);
	return (param->ret);
}
