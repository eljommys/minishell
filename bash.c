/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 19:50:12 by marvin            #+#    #+#             */
/*   Updated: 2020/11/17 19:50:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_path(char *str, char **path)
{
	int		i;
	int		len;
	char	*filename;
	char	*new;
	char	*aux;

	skip_spaces(&str);
	skip_spaces(path);
	new = ft_strdup(*path);
	len = ft_strlen(*path);
	if (!ft_memcmp(str, "/", 1))
		*path = ft_strdup(str);
	else
	{
		i = 0;
		while (!ft_memcmp(str + i, "../", 3))
			i += 3;
		filename = ft_strdup(str + i);
		i /= 3;
		while (i-- > 0)
		{
			while (new[len] != '/')
				len--;
			len--;
		}
		new[len + 1] = 0;
		aux = ft_strjoin(new, "/");
		free(new);
		new = ft_strjoin(aux, filename);
		free(aux);
		free(filename);
		*path = new;
	}
}

/*
**	0 = plain text, 1 = binary, 2 = folder
*/

static void	check_file_type(char *path, char **envp, char *str)
{
	DIR				*dir;
	struct dirent	*d;
	char			*filename;
	int				len;
	char			*line;
	int				fd;
	char			**argv;
	int				argc;
	int				i;

	len = ft_strlen_spa(path);
	if (len > 1)
	{
		while (path[len - 1] != '/')
			len--;
	}
	filename = ft_strdup(path + len);
	if (!(dir = opendir(path)))
	{
		fd = open(path, O_RDONLY, 0666);
		while (get_next_line(fd, &line))
		{
			argc = count_args(line);
			argv = (char **)ft_calloc(sizeof(char *), argc + 1);
			if (argc)
				set_args(argv, line, argc);
			check_command(line, argv, envp);
			free_env(argv);
		}
		close(fd);
	}
	else
	{
		write(1, "-bash: ", 7);
		ft_putstr_fd(str, 1);
		write(1, ": Is a directory\n", 17);
		closedir(dir);
	}
}

void		bash_command(char *str, char **argv, char **envp)
{
	char	buff[4097];
	char	*path;
	char	*start;
	int		status[2];
	int		type;

	skip_spaces(&str);
	start = str;
	if (ft_memcmp(str, "/", 1))
		str += (!ft_memcmp(str, "./", 2)) ? 2 : 0;
	path = getcwd(buff, 4096);
	set_path(str, &path);
	status[0] = 0;
	if (!fork() && execve(path, argv, envp) == -1)
	{
		check_file_type(path, envp, start);
		status[0] = 1;
	}
	else
		wait(&status[1]);
	free(path);
	if (status[0])
		exit(0);
}
