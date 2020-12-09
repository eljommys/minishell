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
	char	*args[3];

	child = fork();
	if (child < 0)
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

static char	*read_cmd(void)
{
	static char	buff[4097];
	int			i;
	int			x;
	int			ret;

	ft_bzero(buff, 4097);
	ft_stty("raw");
	i = 2;
	x = 0;
	while (1)
	{
		if ((ret = cmd_handler(buff, &x, &i)) == 2)
			continue ;
		else if (ret == 1)
			break;
	}
	ft_stty("cooked");
	return (buff);
}

int			get_cmd(t_data *param)
{
	put_prompt(param->envp);
	param->str = read_cmd();
	if (!param->str)
		return (1);
	return (0);
}
