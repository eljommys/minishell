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
		if (*str != ' ' && *str != '\t')
		{
			i++;
			str += ft_strlen_spa(str);
		}
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
		argv[i] = ft_strldup(str, len);
		str += len;
		i++;
	}
}

static int		is_coincidence(char *str, char **envp, DIR **dir, struct dirent **d)
{
	int	is;

	*dir = opendir("/bin");
	if(!(*dir))
		exit_command(str, envp);
	is = 0;
	while(*d = readdir(*dir))
		if (!ft_memcmp(str, (*d)->d_name, ft_strlen((*d)->d_name)))
		{
			is = 1;
			break ;
		}
		else if (!(*d))
			break ;
	return (is);
}

int		check_bin(char *str, char **envp)
{
	DIR				*dir;
	struct dirent	*d;
	char			*path;
	int				status_argc[4];
	char			**argv;

	skip_spaces(&str);
	if (status_argc[3] = is_coincidence(str, envp, &dir, &d))
	{
		status_argc[2] = count_args(str);
		argv = (char **)ft_calloc(sizeof(char *), (status_argc[2] + 1));
		if (status_argc[2])
			set_args(argv, str, status_argc[2]);
		path = ft_strjoin("/bin/", d->d_name);
		status_argc[0] = 0;
		if (!fork() && execve(path, argv, envp))
		{
			write(1, "Coudn't execute command\n", 24);
			status_argc[0] = 1;
		}
		else
			wait(&status_argc[1]);
		free(path);
		if (status_argc[0])
			exit(0);
		free_env(argv);
	}
	closedir(dir);
	return (status_argc[3]);
}
