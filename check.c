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
	if (!ft_memcmp(str + 5, "-n ", 3))
	{
		write(1, str + 8, ft_strlen(str + 8));
		return ;
	}
	write(1, str + 5, ft_strlen(str + 5));
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
				!ft_memcmp(str, "close", 5))
			close_command(str);
	}
}
