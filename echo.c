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

void			set_fd(char *str, int *fd)
{
	char	*path;
	int		len;
	char	buff[4097];
	char	c;

	*fd = 1;
	while (*str && *str != '>')
		str++;
	if (*str == '>')
	{
		len = ft_strlen(str);
		while (str[len] != '>')
			len--;
		len++;
		path = getcwd(buff, 4096);
		printf("str = %s\n", str + len);
		set_path(str + len, &path);
		printf("path = %s\n", path);
		if (*(str + len - 2) == '>')
		{
			printf("añadir\n");
			*fd = open(path, O_RDWR || O_CREAT);
			while (1)
			{
				len = read(*fd, &c, 1);
				printf("c = %c\n", c);
				printf("len = %d\n", len);
				if (!len || len == -1)
					break ;
			}
			//while ((len == read(*fd, &c, 1)) && len != -1);
		}
		else
			*fd = open(path, O_CREAT || O_WRONLY);
		if (*fd == -1)
			write(1, "Couldn't open file\n", 19);
		free(path);
	}
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

void			echo_command(char *str)
{
	int		is_flag;
	int		len;
	int		fd;

	is_flag = 0;
	fd = 1;
	str += 5;
	skip_spaces(&str);
	if (!ft_memcmp(str, "-n ", 3))
	{
		is_flag = 1;
		str += 3;
	}
	//set_fd(str, &fd);
	write_words(str, fd);
	if (!is_flag)
		write(fd, "\n", 1);
	if (fd != 1)
		close(fd);
}
