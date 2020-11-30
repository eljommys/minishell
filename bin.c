/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 22:36:37 by marvin            #+#    #+#             */
/*   Updated: 2020/11/30 18:07:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*is_coincidence(char *s, DIR **dir, struct dirent **d, char **envp)
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
			if (!ft_memcmp(s, (*d)->d_name, ft_strlen(s) + 1))
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

void		set_in(char *str)
{
	char	*file;
	int		fd;

	while (*str && *str != '<')
		str++;
	if (*str)
	{
		str++;
		skip_spaces(&str);
		file = ft_strldup(str, ft_strlen_spa(str));
		fd = open(file, O_RDONLY, 0666);
		if (fd < 0)
		{
			ft_putstr_fd("Couldn't read from file.\n", 1);
			return ;
		}
		dup2(fd, 0);
		free(file);
	}
}

static void	exec_bin(int fd, char *str, char *path, char **envp)
{
	int 	flag;
	int		argc;
	char	**argv;

	argc = count_args(str);
	argv = (char **)ft_calloc(sizeof(char *), (argc + 1));
	if (argc)
		set_args(argv, str, argc);
	if (!fork())
	{
		set_in(str);
		if (fd > 1)
			dup2(fd, 1);
		if (execve(path, argv, envp))
			write(1, "Coudn't execute command\n", 24);
	}
	else
		wait(&flag);
	free(path);
	free_env(argv);
}

int			check_bin(int fd, char *str, char *path, char **envp)
{
	DIR				*dir;
	struct dirent	*d;
	char			*pre_path;
	int				flag;
	char			*name;

	name = ft_strldup(str, ft_strlen_spa(str));
	pre_path = is_coincidence(name, &dir, &d, envp);
	free(name);
	flag = 0;
	if (pre_path && *pre_path)
	{
		flag = 1;
		path = ft_strjoin(pre_path, d->d_name);
		exec_bin(fd, str, path, envp);
		closedir(dir);
	}
	free(pre_path);
	return (flag);
}
