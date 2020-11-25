/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 00:01:09 by marvin            #+#    #+#             */
/*   Updated: 2020/11/17 00:01:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_command(char **envp, char *str)
{
	char	*aux;

	str += 3;
	aux = str;
	if (*aux == '~')
	{
		aux = ft_strjoin(get_env(envp, "HOME"), str + 1);
		chdir(aux);
	}
	else
		chdir(str);
	if (str != aux)
		free(aux);
}

void	pwd_command(int fd)
{
	char *cwd;
	char buff[4097];

	cwd = getcwd(buff, 4096);
	ft_putstr_fd(cwd, fd);
	write (fd, "\n", 1);
}

void	exit_command(char *str, char **envp)
{
	free(str);
	free_env(envp);
	exit(0);
}
