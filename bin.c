/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 22:36:37 by marvin            #+#    #+#             */
/*   Updated: 2020/11/23 22:36:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_args(char *str)
{
	int		i;

	i = 0;
	while (*str && *str != '|' && *str != '<' && *str != '&' && *str != '>' &&
		*str != ';')
	{
		skip_spaces(&str);
		i++;
		str += ft_strlen_spa(str);
	}
	return (i);
}

static int		ft_strlen_quote(char *str)
{
	int		i;
	char	quote;

	quote = *str;
	str++;
	i = 0;
	while (str[i] && str[i] != quote)
		i++;
	return (i);
}

void		set_args(char **argv, char *str, int argc)
{
	int i;
	int len;

	i = 0;
	while (i < argc)
	{
		skip_spaces(&str);
		len = ft_strlen_spa(str);
		if (len)
		{
			if (*str == '"' || *str == '\'')
			{
				len = ft_strlen_quote(str);
				str++;
			}
			argv[i] = ft_strldup(str, len);
			str++;
		}
		str += len;
		i++;
	}
}

static char		*is_coincidence(char *str, DIR **dir, struct dirent **d, char **envp)
{
	char	*path_str;
	char	**paths;
	char	*path;
	char	*name;
	int		i;

	path_str = get_env(envp, "PATH");
	paths = ft_split(path_str, ':');
	name = ft_strldup(str, ft_strlen_spa(str));
	i = 0;
	while (i < 8 && paths[i])
	{
		*dir = opendir(paths[i]);
		while(*d = readdir(*dir))
		{
			if (!ft_memcmp(name, (*d)->d_name, ft_strlen(name) + 1))
			{
				path = ft_strjoin(paths[i], "/");
				free(name);
				free_env(paths);
				return (path);
			}
		}
		closedir(*dir);
		i++;
	}
	free_env(paths);
	free(name);
	return (NULL);
}

void	set_in(char *str)
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

int		check_bin(char *str, char **envp, int fd)
{
	DIR				*dir;
	struct dirent	*d;
	char			*path;
	char			*pre_path;
	int				status_argc[3];
	char			**argv;

	pre_path = is_coincidence(str, &dir, &d, envp);
	status_argc[2] = 0;
	if (pre_path && *pre_path)
	{
		status_argc[2] = 1;
		status_argc[1] = count_args(str);
		argv = (char **)ft_calloc(sizeof(char *), (status_argc[1] + 1));
		if (status_argc[1])
			set_args(argv, str, status_argc[1]);
		path = ft_strjoin(pre_path, d->d_name);
		if (!fork())
		{
			set_in(str);
			if (fd > 1)
				dup2(fd, 1);
			if (execve(path, argv, envp))
				write(1, "Coudn't execute command\n", 24);
		}
		else
			wait(&status_argc[0]);
		free(path);
		free_env(argv);
		closedir(dir);
	}
	free(pre_path);
	return (status_argc[2]);
}
