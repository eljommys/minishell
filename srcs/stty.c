/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stty.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 15:06:32 by marvin            #+#    #+#             */
/*   Updated: 2020/12/09 15:06:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_stty(char *action)
{
	pid_t	child;
	char 	*args[3];

	if ((child == fork()) < 0)
		exit (1);
	if (!child)
	{
		args[0] = "/bin/stty";
		args[1] = action;
		args[0] = NULL;
		execve(args[0], args, NULL);
		exit (1);
	}
	if (child > 0)
		wait(NULL);
}

void		logout(void)
{
	ft_stty("cooked");
	ft_putstr_fd("logout\n", 1);
	exit (0);
}
