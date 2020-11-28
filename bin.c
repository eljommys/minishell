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
	int				status_argc[4];
	char			**argv;

	if (status_argc[3] = is_coincidence(str, &dir, &d))
	{
		status_argc[2] = count_args(str);
		argv = (char **)ft_calloc(sizeof(char *), (status_argc[2] + 1));
		if (status_argc[2])
			set_args(argv, str, status_argc[2]);
		path = ft_strjoin("/bin/", d->d_name);
		status_argc[0] = 0;
		if (!fork())
		{
			if (fd > 1)
				dup2(fd, 1);
			if(execve(path, argv, envp))
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
/*
static char        *is_coincidence(char *str, DIR **dir, struct dirent **d, char **envp)
{
    char    *path_str;
    char    **paths;
    int        i;
    char    *path;

    path_str = get_env(envp, "PATH");
    paths = ft_split(path_str, ':');
    i = 0;
    while (paths[i])
    {
        *dir = opendir(paths[i]);
        while(*d = readdir(*dir))
        {
            if (!ft_memcmp(str, (*d)->d_name, ft_strlen_spa(str) + 1))
            {
                path = ft_strjoin(paths[i], "/");
                free_env(paths);
                return (path);
            }
        }
        closedir(*dir);
        i++;
    }
    free_env(paths);
    return (0);
}

int        check_bin(char *str, char **envp, int fd)
{
    DIR                *dir;
    struct dirent    *d;
    char            *path;
    char            *pre_path;
    int                status_argc[3];
    char            **argv;

    if (pre_path = is_coincidence(str, &dir, &d, envp))
    {
        status_argc[1] = count_args(str);
        argv = (char **)ft_calloc(sizeof(char *), (status_argc[1] + 1));
        if (status_argc[1])
            set_args(argv, str, status_argc[1]);
        printf("d->name = %s\n", d->d_name);
        printf("pre_path = %s\n", pre_path);
        path = ft_strjoin(pre_path, d->d_name);
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
    free(pre_path);
    return (status_argc[2]);
}
*/
