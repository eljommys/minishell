/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 00:01:09 by marvin            #+#    #+#             */
/*   Updated: 2020/11/17 00:01:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	echo_command(char *str)
{
	int	is_flag;
	int	len;

	is_flag = 0;
	str += 5;
	if (!ft_memcmp(str, "-n ", 3))
	{
		is_flag = 1;
		str += 3;
	}
	len = ft_strlen(str);
	if (str[0] == '"' || str[0] == '\'')
		if (str[len - 1] == str[0])
		{
			str++;
			len -= 2;
		}
	write(1, str, len);
	if (!is_flag)
		write(1, "\n", 1);
}

static void pwd_command(void)
{
	char *cwd;
	char buff[4097];

	cwd = getcwd(buff, 4096);
	ft_putstr_fd(cwd, 1);
	write (1, "\n", 1);
}

static void	exit_command(char *str)
{
	free(str);
	exit(0);
}

void		check_command(char *str)
{
	if (str)
	{
		if (!ft_memcmp(str, "echo ", 5))
			echo_command(str);
		else if (!ft_memcmp(str, "pwd", 3))
			pwd_command();
		else if (!ft_memcmp(str, "./", 2) || !ft_memcmp(str, "../", 3) ||
							!ft_memcmp(str, "/", 1))
			bash_command(str);
		else if (!ft_memcmp(str, "quit", 5) || !ft_memcmp(str, "exit", 5) ||
				!ft_memcmp(str, "close", 6) || !ft_memcmp(str, "q", 2))
			exit_command(str);
		free(str);
	}
}
