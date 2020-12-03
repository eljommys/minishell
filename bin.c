/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 22:36:37 by marvin            #+#    #+#             */
/*   Updated: 2020/12/03 12:01:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void	set_in(char **argv)
{
	int		fd;
	int		i;

	i = 0;
	while (argv[i] && ft_memcmp(argv[i], "<", 2))
		i++;
	if (argv[i])
	{
		fd = open(argv[i + 1], O_RDONLY, 0666);
		if (fd < 0)
		{
			ft_putstr_fd("Couldn't read from file.\n", 1);
			return ;
		}
		dup2(fd, 0);
	}
}

static void	exec_bin(int fd, char *path, t_data *param)
{
	if (!fork())
	{
		set_in(param->argv);
		if (fd > 1)
			dup2(fd, 1);
		if (execve(path, param->argv, param->envp))
			write(1, "Coudn't execute command\n", 24);
	}
	wait(&(param->ret));
	param->ret /= 256;
	free(path);
}

static char	*search_bin(char *str, DIR **dir, struct dirent **d, char **envp)
{
	char	*path_str;
	char	**paths;
	char	*path;
	int		i;

	path_str = get_env(envp, "PATH");
	paths = ft_split(path_str, ':');
	i = -1;
	while (++i < 8 && paths[i])
	{
		*dir = opendir(paths[i]);
		while (*d = readdir(*dir))
		{
			if (!ft_memcmp(str, (*d)->d_name, ft_strlen(str) + 1))
			{
				path = ft_strjoin(paths[i], "/");
				free_env(paths);
				return (path);
			}
		}
		closedir(*dir);
	}
	free_env(paths);
	return (NULL);
}

int			check_bin(int fd, t_data *param)
{
	DIR				*dir;
	struct dirent	*d;
	char			*pre_path;
	char			*path;

	pre_path = search_bin(param->argv[0], &dir, &d, param->envp);
	param->ret = 0;
	if (pre_path && *pre_path)
	{
		path = ft_strjoin(pre_path, d->d_name);
		exec_bin(fd, path, param);
		closedir(dir);
	}
	else
		param->ret = 1;
	free(pre_path);
	return (param->ret);
}
