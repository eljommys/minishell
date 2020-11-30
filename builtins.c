/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 00:01:09 by marvin            #+#    #+#             */
/*   Updated: 2020/12/01 00:38:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_command(char *str, char **envp)
{
	free(str);
	free_env(envp);
	exit(0);
}

static void	cd_command(char **envp, char *str)
{
	char	*aux;

	if (str[2] == 0)
		str = "cd ~";
	str += 3;
	aux = str;
	if (*str == '~')
		aux = ft_strjoin(get_env(envp, "HOME"), str + 1);
	chdir(aux);
	if (aux != str)
		free(aux);
}

static void	pwd_command(int fd)
{
	char *cwd;
	char buff[4097];

	cwd = getcwd(buff, 4096);
	ft_putstr_fd(cwd, fd);
	write(fd, "\n", 1);
}

int			check_builtins(int fd, char *start, char *str, t_data *param)
{
	if (!ft_memcmp(str, "echo ", 5))
		echo_command(param->envp, str, fd);
	else if (!ft_memcmp(str, "pwd", 4) || !ft_memcmp(str, "pwd ", 4))
		pwd_command(fd);
	else if (!ft_memcmp(str, "cd ", 3) || !ft_memcmp(str, "cd", 3))
		cd_command(param->envp, str);
	else if (!ft_memcmp(str, "env", 4) || !ft_memcmp(str, "env ", 4))
		env_command(param->envp, fd);
	else if (!ft_memcmp(str, "./", 2) || !ft_memcmp(str, "../", 3) ||
			 !ft_memcmp(str, "/", 1))
		bash_command(str, param);
	else if (!ft_memcmp(str, "export ", 7))
		param->envp = export_command(str, param->envp);
	else if (!ft_memcmp(str, "unset ", 6))
		param->envp = unset_command(str, param->envp);
	else if (!ft_memcmp(str, "exit", 4) || !ft_memcmp(str, "q", 1))
		exit_command(start, param->envp);
	else
		return (0);
	return (1);
}
