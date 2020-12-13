/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 19:50:12 by marvin            #+#    #+#             */
/*   Updated: 2020/12/13 13:46:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_type(t_data *param, char *str, char *path)
{
	DIR			*dir;
	int			fd;
	char		**cmds;

	if (errno == ENOENT || errno == EACCES)
	{
		ft_putstrs_fd("bash: ", str, ": ", 2);
		ft_putstrs_fd(strerror(errno), "\n", 0, 2);
		param->ret = (errno == ENOENT) ? 127 : 126;
	}
	else if (!(dir = opendir(path)))
	{
		fd = open(path, O_RDONLY, 0666);
		free(param->str);
		while (get_next_line(fd, &(param->str)))
		{
			cmds = param->cmds;
			parser(param);
			param->cmds = cmds;
		}
		close(fd);
	}
	else
	{
		ft_putstrs_fd("-bash: ", str, ": Is a directory\n", 2);
		param->ret = 126;
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
	aux = ft_strldup(*new, len);
	free(*new);
	*new = ft_strjoin(aux, "/");
	free(aux);
	aux = ft_strjoin(*new, filename);
	free(*new);
	*new = aux;
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
		return ;
	}
	free(new);
}

static void	child_sig_handler_bash(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		exit(0);
	}
}

void		bash_command(t_data *param)
{
	char	buff[4097];
	char	*path;
	char	*start;

	start = param->argv[0];
	if (ft_memcmp(param->argv[0], "/", 1))
		param->argv[0] += (!ft_memcmp(param->argv[0], "./", 2)) ? 2 : 0;
	path = getcwd(buff, 4096);
	set_path(param->argv[0], &path);
	if (!fork())
	{
		signal(SIGINT, child_sig_handler_bash);
		if (execve(path, param->argv, param->envp))
			check_type(param, start, path);
		exit(param->ret);
	}
	else
		wait(&param->ret);
	param->ret /= 256;
	free(path);
	param->argv[0] = start;
}
