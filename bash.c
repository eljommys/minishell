/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 19:50:12 by marvin            #+#    #+#             */
/*   Updated: 2020/11/30 17:44:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_type(char **argv, char **envp, char *str, char *path)
{
	DIR		*dir;
	char	*line;
	int		fd;
	int		argc;

	if (!(dir = opendir(path)))
	{
		fd = open(path, O_RDONLY, 0666);
		while (get_next_line(fd, &line))
		{
			argc = count_args(line);
			argv = (char **)ft_calloc(sizeof(char *), argc + 1);
			if (argc)
				set_args(argv, line, argc);
			envp = check_pipe(line, argv, envp);
			free_env(argv);
		}
		close(fd);
	}
	else
	{
		ft_putstrs_fd("-bash: ", str, ": Is a directory\n", 1);
		closedir(dir);
	}
}

static void	set_filename(int len, char **new, char *str)
{
	int		i;
	char	*filename;
	char	*aux;

	i = 0;
	while (!ft_memcmp(str + i, "../", 3))
		i += 3;
	filename = ft_strdup(str + i);
	i /= 3;
	while (i-- > 0)
	{
		while ((*new)[len] != '/')
			len--;
		len--;
	}
	(*new)[len + 1] = 0;
	aux = ft_strjoin(*new, "/");
	free(*new);
	*new = ft_strjoin(aux, filename);
	free(aux);
	free(filename);
}

static void	set_path(char *str, char **path)
{
	int		len;
	char	*new;

	new = ft_strdup(*path);
	len = ft_strlen(*path);
	if (!ft_memcmp(str, "/", 1))
		*path = ft_strdup(str);
	else
	{
		set_filename(len, &new, str);
		*path = new;
	}
}

void		bash_command(char *str, char **argv, char **envp)
{
	char	buff[4097];
	char	*path;
	char	*start;
	int		status[2];

	start = str;
	if (ft_memcmp(str, "/", 1))
		str += (!ft_memcmp(str, "./", 2)) ? 2 : 0;
	path = getcwd(buff, 4096);
	set_path(str, &path);
	status[0] = 0;
	if (!fork())
	{
		if (execve(path, argv, envp))
			check_type(argv, envp, start, path);
		status[0] = 1;
	}
	else
		wait(&status[1]);
	free(path);
	if (status[0])
		exit(0);
}
