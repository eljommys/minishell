/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:16:03 by marvin            #+#    #+#             */
/*   Updated: 2020/11/16 15:16:03 by marvin           ###   ########.fr       */
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

static char		**check_command(char *str, char **argv, char **envp)
{
	int	fd;
	char *start;

	start = str;
	while (str && *str)
	{
		fd = set_fd(str);
		skip_spaces(&str);
		if (!ft_memcmp(str, "echo ", 5))
			echo_command(str, fd);
		else if (!ft_memcmp(str, "pwd", 4) || !ft_memcmp(str, "pwd ", 4))
			pwd_command(fd);
		else if (!ft_memcmp(str, "cd ", 3))
			cd_command(envp, str);
		else if (!ft_memcmp(str, "env", 4) || !ft_memcmp(str, "env ", 4))
			env_command(envp, fd);
		else if (!ft_memcmp(str, "./", 2) || !ft_memcmp(str, "../", 3) ||
				!ft_memcmp(str, "/", 1))
			bash_command(str, argv, envp);
		else if (!ft_memcmp(str, "export ", 7))
			envp = export_command(str, envp);
		else if (!ft_memcmp(str, "unset ", 6))
			envp = unset_command(str, envp);
		else if (!ft_memcmp(str, "quit", 4) || !ft_memcmp(str, "exit", 4) ||
				!ft_memcmp(str, "close", 5) || !ft_memcmp(str, "q", 1))
			exit_command(str, envp);
		else
			check_bin(str, argv, envp);
		if (fd > 1)
			close(fd);
		move_next(&str);
	}
	free(start);
	return (envp);
}

static int	add_char(char **str, char c)
{
	char	*new;
	int		len;
	int		i;

	if (!(*str))
	{
		if (!(*str = (char *)malloc(sizeof(char) * 2)))
			return (-1);
		(*str)[0] = c;
		(*str)[1] = 0;
		return (0);
	}
	len = ft_strlen(*str);
	if (!(new = (char *)malloc(sizeof(char) * (len + 2))))
		return (-1);
	i = -1;
	while (++i < len)
		new[i] = (*str)[i];
	new[i] = c;
	new[i + 1] = 0;
	if (len)
		free(*str);
	*str = new;
	return (0);
}

static char	*relative_path(char *cwd, char **envp)
{
	char	*home;
	char	*path;

	home = get_env(envp, "HOME");
	if (ft_memcmp(cwd, home, ft_strlen(home)))
		path = ft_strdup(cwd);
	else
		path = ft_strjoin("~", cwd + ft_strlen(home));
	return (path);
}

int			main(int argc, char **argv, char **envp)
{
	char	c;
	char	*str;
	char	*cwd;
	char	buff[4097];

	envp = copy_env(envp, 0);
	while (1)
	{
		str = 0;
		cwd = relative_path(getcwd(buff, 4096), envp);
		write(1, "\033[0;32mminishell:\033[0;0m\033[\033[0;34m", 32);
		ft_putstr_fd(cwd, 1);
		write(1, "\033[0;0m$ ", 8);
		free(cwd);
		while (1)
		{
			if (read(1, &c, 1) == 1 && c == '\n')
				break ;
			if (add_char(&str, c))
				return (-1);
		}
		envp = check_command(str, argv, envp);
	}
}
