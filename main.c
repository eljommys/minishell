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

static char 	**check_command(char *str, char **argv, char **envp)
{
	if (str)
	{
		if (!ft_memcmp(str, "echo ", 5))
			echo_command(str);
		else if (!ft_memcmp(str, "pwd", 4))
			pwd_command();
		else if (!ft_memcmp(str, "ls", 3))
			ls_command();
		else if (!ft_memcmp(str, "cd ", 3))
			cd_command(str);
		else if (!ft_memcmp(str, "env", 4))
			env_command(envp);
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
		free(str);
	}
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

char		**copy_env(char **envp, int add)
{
	int		len;
	int		i;
	char	**cpy;

	len = 0;
	while (envp[len])
		len++;
	if (!(cpy = (char **)malloc(sizeof(char *) * (len + add + 1))))
		return (0);
	i = -1;
	while (++i < len)
		cpy[i] = ft_strdup(envp[i]);
	cpy[i] = 0;
	return (cpy);
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
		cwd = getcwd(buff, 4096);
		write(1, "\033[0;32mminishell:\033[0;0m\033[\033[0;34m", 32);
		ft_putstr_fd(cwd, 1);
		write(1, "\033[0;0m$ ", 8);
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
