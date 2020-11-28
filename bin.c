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
			argv[i] = ft_strldup(str, len);
		str += len;
		i++;
	}
}

static int		is_coincidence(char *str, DIR **dir, struct dirent **d)
{
	int	is;

	*dir = opendir("/bin");
	is = 0;
	while(*d = readdir(*dir))
		if (!ft_memcmp(str, (*d)->d_name, ft_strlen((*d)->d_name)))
		{
			is = 1;
			break ;
		}
	return (is);
}

int		check_bin(char *str, char **envp, int fd)
{
	DIR				*dir;
	struct dirent	*d;
	char			*path;
	int				status_argc[3];
	char			**argv;

	if (status_argc[2] = is_coincidence(str, &dir, &d))
	{
		status_argc[1] = count_args(str);
		argv = (char **)ft_calloc(sizeof(char *), (status_argc[1] + 1));
		if (status_argc[1])
			set_args(argv, str, status_argc[1]);
		path = ft_strjoin("/bin/", d->d_name);
		if (!fork())
		{
			if (fd > 1)
				dup2(fd, 1);
			if (execve(path, argv, envp))
				write(1, "Coudn't execute command\n", 24);
			exit(0);
		}
		else
			wait(&status_argc[0]);
		free(path);
		free_env(argv);
	}
	closedir(dir);
	return (status_argc[2]);
}
