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

static void	close_command(char *str)
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
		else if (!ft_memcmp(str, "quit", 5) || !ft_memcmp(str, "exit", 5) ||
				!ft_memcmp(str, "close", 5) || !ft_memcmp(str, "q", 2))
			close_command(str);
		free(str);
	}
}
