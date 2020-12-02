/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 00:01:09 by marvin            #+#    #+#             */
/*   Updated: 2020/12/02 14:07:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void exit_command(char *str, t_data *param)
{
	free(str);
	free_env(param->envp);
	free_env(param->argv);
	free(param);
	exit(0);
}

static void change_dir(char *path, t_data *param)
{
	char 		buff[4097];
	char		*oldpwd;
	struct stat s;

	oldpwd = getcwd(buff, 4096);
	if (chdir(path) == 0)
	{
		param->argc = 2;
		free(param->argv[1]);
		param->argv[1] = ft_strjoin("OLDPWD=", oldpwd);
		param->envp = export_command(param);
		free(param->argv[1]);
		param->argv[1] = ft_strjoin("PWD=", getcwd(buff, 4096));
		param->envp = export_command(param);
	}
	else if (ft_putstrs_fd("-bash: cd: ", 0, 0, 1) && lstat(path, &s) != -1)
	{
		if (s.st_mode & S_IFDIR)
			ft_putstrs_fd(0, param->argv[1], ": permission denied\n", 1);
		else
			ft_putstrs_fd(0, param->argv[1], ": Not a directory\n", 1);
	}
	else
		ft_putstrs_fd(0, param->argv[1], ": No such file or directory\n", 1);
}

void cd_command(t_data *param)
{
	char *path;

	if (!param->argv[1] || !ft_strncmp(param->argv[1], "--", 3) ||
		!ft_strncmp(param->argv[1], "~", 2))
		path = get_env(param->envp, "HOME");
	else if (!ft_strncmp(param->argv[1], "-", 2))
		path = get_env(param->envp, "OLDPWD");
	else if (param->argv[2])
	{
		path = NULL;
		if (param->argv[3])
			ft_putstr_fd("-bash: cd: too many arguments\n", 1);
	}
	else
		path = param->argv[1];
	change_dir(path, param);
}

static void pwd_command(int fd, t_data *param)
{
	char *cwd;
	char buff[4097];

	cwd = getcwd(buff, 4096);
	ft_putstr_fd(cwd, fd);
	write(fd, "\n", 1);
}

void echo_command(t_data *param, int fd)
{
	int i;

	i = (!ft_memcmp(param->argv[1], "-n", 3)) ? 1 : 0;
	while (++i < param->argc)
	{
		ft_putstr_fd(param->argv[i], fd);
		if (i < param->argc - 1)
			write(1, " ", 1);
	}
	if (ft_memcmp(param->argv[1], "-n", 3))
		write(fd, "\n", 1);
	if (fd != 1)
		close(fd);
}

int check_builtins(int fd, char *start, t_data *param)
{
	if (!ft_memcmp(param->argv[0], "echo", 5))
		echo_command(param, fd);
	else if (!ft_memcmp(param->argv[0], "pwd", 4))
		pwd_command(fd, param);
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
		exit_command(start, param);
	else
		return (0);
	return (1);
}
