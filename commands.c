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

void	pwd_command(void)
{
	char *cwd;
	char buff[4097];

	cwd = getcwd(buff, 4096);
	ft_putstr_fd(cwd, 1);
	write (1, "\n", 1);
}

void	exit_command(char *str)
{
	free(str);
	exit(0);
}

void	ls_command(void)
{
	DIR				*dir;
	struct dirent	*d;

	dir = opendir(".");
	if(dir == NULL)
	{
		ft_putstr_fd("Error! Unable to open directory.\n", 1);
		exit(1);
	}
	while((d = readdir(dir)) != NULL)
	{
		if(d->d_name[0] != '.')
		{
			ft_putstr_fd(d->d_name , 1);
			write(1, "  ", 2);
		}
	}
	write(1, "\n", 1);
}

void	cd_command(char *str)
{
	str += 3;
	chdir(str);
}
