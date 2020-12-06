/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 22:36:37 by marvin            #+#    #+#             */
/*   Updated: 2020/12/06 10:18:01 by marvin           ###   ########.fr       */
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
	int	status;

	signal(SIGINT, child_sig_handler);
	if (!fork())
	{
		set_in(param->argv);
		if (fd > 1)
			dup2(fd, 1);
		if (execve(path, param->argv, param->envp) && errno == EACCES)
		{
			ft_putstrs_fd("-bash: ", param->argv[0], ": ", 1);
			ft_putstrs_fd(strerror(errno), "\n", 0, 1);
		}
		exit(0);
	}
	wait(&status);
	free(path);
}

static char	**split_path(t_data *param, char *str)
{
	char *path_str;
	char **paths;

	path_str = get_env(param->envp, "PATH");
	if (path_str)
		paths = ft_split(path_str, ':');
	else
	{
		ft_putstrs_fd("-bash: ", str, ": No such file or directory\n", 1);
		param->ret = 0;
		return (NULL);
	}
	return (paths);
}

static char	*search_bin(char *str, DIR **dir, struct dirent **d, t_data *param)
{
	char		**paths;
	char		*path;
	int			i;

	if (!(paths = split_path(param, str)))
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		*dir = opendir(paths[i]);
		while ((*dir) && errno != EACCES && (*d = readdir(*dir)))
		{
			if (!ft_memcmp(str, (*d)->d_name, ft_strlen(str) + 1))
			{
				path = ft_strjoin(paths[i], "/");
				free_matrix(paths);
				return (path);
			}
		}
		closedir(*dir);
	}
	free_matrix(paths);
	return (NULL);
}

int			check_bin(int fd, t_data *param)
{
	DIR				*dir;
	struct dirent	*d;
	char			*pre_path;
	char			*path;

	param->ret = 1;
	pre_path = search_bin(param->argv[0], &dir, &d, param);
	if (pre_path && *pre_path)
	{
		param->ret = 0;
		path = ft_strjoin(pre_path, d->d_name);
		exec_bin(fd, path, param);
		closedir(dir);
		free(pre_path);
	}
	return (param->ret);
}
