/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 00:01:09 by marvin            #+#    #+#             */
/*   Updated: 2020/12/01 14:29:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_command(char *str, t_data *param)
{
	free(str);
	free_env(param->envp);
	free_env(param->argv);
	free(param);
	exit(0);
}

static void	cd_command(t_data *param)
{
	char	*aux;

	if (param->argc <= 2)
	{
		if (!param->argv[1] || !ft_memcmp(param->argv[1], "~", 2))
			chdir(get_env(param->envp, "HOME"));
		else
			chdir(param->argv[1]);
	}
	else
		ft_putstr_fd("Wrong numer of arguments in 'pwd'!\n", 1);
	/*if (str[2] == 0)
		str = "cd ~";
	str += 3;
	aux = str;
	if (*str == '~')
		aux = ft_strjoin(get_env(envp, "HOME"), str + 1);
	chdir(aux);
	if (aux != str)
		free(aux);*/
}

static void	pwd_command(int fd, t_data *param)
{
	char *cwd;
	char buff[4097];

	if (param->argc != 1)
	{
		ft_putstr_fd("Wrong numer of arguments in 'pwd'!\n", 1);
		return ;
	}
	cwd = getcwd(buff, 4096);
	ft_putstr_fd(cwd, fd);
	write(fd, "\n", 1);
}

int			check_builtins(int fd, char *start, t_data *param)
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
