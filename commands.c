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

void	cd_command(char *str)
{
	str += 3;
	chdir(str);
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

void	check_bin(char *str, char **argv, char **envp)
{
	DIR				*dir;
	struct dirent	*d;
	int				is;
	char			*path;
	int				status[2];

	skip_spaces(&str);
	dir = opendir("/bin");
	if(dir == NULL)
		exit(1);
	is = 0;
	while(d = readdir(dir))
		if (!ft_memcmp(str, d->d_name, ft_strlen(d->d_name)))
		{
			is = 1;
			break ;
		}
		else if (!d)
			break ;
	if (is)
	{
		path = ft_strjoin("/bin/", d->d_name);
		status[0] = 0;
		if (!fork() && execve(path, argv, envp))
		{
			write(1, "Coudn't execute command\n", 24);
			status[0] = 1;
		}
		else
			wait(&status[1]);
		free(path);
		if (status[0])
			exit(0);
	}
	closedir(dir);
}
