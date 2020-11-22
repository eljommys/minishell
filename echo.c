/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 13:09:57 by marvin            #+#    #+#             */
/*   Updated: 2020/11/19 13:09:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_strlen_spa(char *str)
{
	int		len;

	len = 0;
	while (*str && *str != ' ' && *str != '>')
	{
		len++;
		str++;
	}
	return (len);
}


void			write_words(char *str, int fd)
{
	int		len;
	char	*start;
	char	str_char;

	skip_spaces(&str);
	start = str;
	while (*str && *str != '>')
	{
		if (str != start)
			write(fd, " ", 1);
		len = ft_strlen_spa(str);
		if (*str == '"' || *str == '\'')
		{
			str_char = *str;
			str++;
			while (*str != str_char)
				write(fd, str++, 1);
			str++;
		}
		else
		{
			write(fd, str, len);
			str += len;
		}
		skip_spaces(&str);
	}
}

void			echo_command(char *str, int fd)
{
	int		is_flag;

	is_flag = 0;
	str += 5;
	skip_spaces(&str);
	if (!ft_memcmp(str, "-n ", 3))
	{
		is_flag = 1;
		str += 3;
	}
	write_words(str, fd);
	if (!is_flag)
		write(fd, "\n", 1);
	if (fd != 1)
		close(fd);
}
