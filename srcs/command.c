/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 18:22:40 by marvin            #+#    #+#             */
/*   Updated: 2020/12/08 21:17:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		set_fd(t_data *param)
{
	int		i;
	int		fd;
	char	c;

	i = 0;
	while (param->argv[i] && ft_memcmp(param->argv[i], ">", 2)
			&& ft_memcmp(param->argv[i], ">>", 3))
		i++;
	if (!param->argv[i])
		return (1);
	else if (!ft_memcmp(param->argv[i], ">", 2))
		return (open(param->argv[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0666));
	fd = open(param->argv[i + 1], O_RDWR | O_CREAT | O_APPEND, 0666);
	while ((i = read(fd, &c, 1)))
		if (i == -1)
		{
			write(1, "Couldn't read file\n", 19);
			break ;
		}
	return (fd);
}

static char		**copy_args1(t_data *param)
{
	int		i;
	char	**args;

	i = 0;
	while (param->argv[i] &&
			ft_memcmp(param->argv[i], ">", 2) &&
			ft_memcmp(param->argv[i], ">>", 3))
		i++;
	args = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	while (param->argv[i] &&
			ft_memcmp(param->argv[i], ">", 2) &&
			ft_memcmp(param->argv[i], ">>", 3))
	{
		args[i] = ft_strdup(param->argv[i]);
		i++;
	}
	return (args);
}

char		**check_command(char *str, t_data *param)
{
	int		fd;
	char	**aux;

	param->argc = count_args(str);
	param->argv = (char **)ft_calloc(sizeof(char *), (param->argc + 1));
	set_args(param->argv, str, param->argc);
	if (param->argv[0] && *(param->argv[0]))
	{
		fd = set_fd(param);
		aux = copy_args1(param);
		free_matrix(param->argv);
		param->argv = aux;
		param->argc = 0;
		while (param->argv[param->argc])
			(param->argc)++;
		param->ret = check_builtins(fd, param);
		if (param->ret == 128 && (param->ret = check_bin(fd, param)) == 1)
		{
			ft_putstrs_fd(0, str, ": command not found.\n", 1);
			param->ret = 127;
		}
		if (fd != 1)
			close(fd);
	}
	free_matrix(param->argv);
	param->argc = 0;
	return (param->envp);
}
