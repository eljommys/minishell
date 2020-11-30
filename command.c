/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 20:43:25 by marvin            #+#    #+#             */
/*   Updated: 2020/12/01 00:43:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int move_next(char **str)
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

static int redirect(char *str)
{
	int		append;
	int		len;
	int		fd;
	char	c;

	fd = 1;
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
	return (fd);
}

static int set_fd(char *str)
{
	int fd;

	fd = 1;
	while (*str && *str != '>')
		str++;
	if (*str == '>')
		fd = redirect(str);
	if (fd < 0)
		write(1, "Couldn't open file\n", 19);
	return (fd);
}

char **check_command(char *str, t_data *param)
{
	int		fd;
	int		built;
	char	*start;
	char	*path;

	start = str;
	while (str && *str)
	{
		fd = set_fd(str);
		skip_spaces(&str);
		built = check_builtins(fd, start, str, param);
		if (!built && !check_bin(fd, str, path, param->envp))
			ft_putstrs_fd("Command \'", str, "\' not found.\n", 1);
		if (fd > 1)
			close(fd);
		move_next(&str);
	}
	if (start)
		free(start);
	return (param->envp);
}
