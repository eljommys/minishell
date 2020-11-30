/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 20:43:25 by marvin            #+#    #+#             */
/*   Updated: 2020/11/29 20:43:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		set_fd(char *str)
{
	int		fd;
	int		append;
	char	c;
	int		len;

	fd = 1;
	while (*str && *str != '>')
		str++;
	if (*str == '>')
	{
		str++;
		append = (*str == '>') ? 1 : 0;
		skip_spaces(&str);
		if (append)
		{
			str++;
			skip_spaces(&str);
			fd = open(str, O_RDWR | O_CREAT | O_APPEND, 0666);
			while (len = read(fd, &c, 1))
				if (len == -1)
				{
					write(1, "Couldn't read file\n", 19);
					break;
				}
		}
		else
			fd = open(str, O_RDWR | O_CREAT | O_TRUNC, 0666);
	}
	if (fd < 0)
		write(1, "Couldn't open file\n", 19);
	return (fd);
}

static int		move_next(char **str)
{
	while (**str && **str != ';')
		(*str)++;
	if (**str)
	{
		(*str)++;
		return (1);
	}
	return (0);
}

static void		check_env(char **str, char **envp)
{
	char	*cpy;
	int		len;
	char	*env;

	cpy = *str;
	if (cpy && *cpy)
	{
		skip_spaces(&cpy);
		if (*cpy == '$')
		{
			cpy++;
			cpy = ft_strldup(cpy, ft_strlen_spa(cpy));
			env = ft_strdup(get_env(envp, cpy));
			free(cpy);
			if (env)
			{
				free(*str);
				*str = env;
			}
		}
	}
}

static int		builtins(int fd, char *start, char *str, char **argv, char ***envp)
{
	if (!ft_memcmp(str, "echo ", 5))
		echo_command(*envp, str, fd);
	else if (!ft_memcmp(str, "pwd", 4) || !ft_memcmp(str, "pwd ", 4))
		pwd_command(fd);
	else if (!ft_memcmp(str, "cd ", 3))
		cd_command(*envp, str);
	else if (!ft_memcmp(str, "env", 4) || !ft_memcmp(str, "env ", 4))
		env_command(*envp, fd);
	else if (!ft_memcmp(str, "./", 2) || !ft_memcmp(str, "../", 3) ||
			!ft_memcmp(str, "/", 1))
		bash_command(str, argv, *envp);
	else if (!ft_memcmp(str, "export ", 7))
		*envp = export_command(str, *envp);
	else if (!ft_memcmp(str, "unset ", 6))
		*envp = unset_command(str, *envp);
	else if (!ft_memcmp(str, "quit", 4) || !ft_memcmp(str, "exit", 4) ||
			!ft_memcmp(str, "close", 5) || !ft_memcmp(str, "q", 1))
		exit_command(start, *envp);
	else
		return (0);
	return (1);
}

char		**check_command(char *str, char **argv, char **envp)
{
	int		fd;
	int		built;
	char	*start;
	char	*path;

	check_env(&str, envp);
	start = str;
	while (str && *str)
	{
		fd = set_fd(str);
		skip_spaces(&str);
		built = builtins(fd, start, str, argv, &envp);
		if (!built && !check_bin(fd, str, path, argv, envp))
		{
			write(1, "Command \'", 9);
			ft_putstr_fd(str, 1);
			write(1, "\' not found.\n", 13);
		}
		if (fd > 1)
			close(fd);
		move_next(&str);
	}
	if (start)
		free(start);
	return (envp);
}
