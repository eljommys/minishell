/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 18:22:40 by marvin            #+#    #+#             */
/*   Updated: 2020/12/10 16:02:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect(t_data *param, int i, int fd)
{
	int		ret;
	char	c;

	while (param->argv[i] && (!ft_memcmp(param->argv[i], ">", 2) ||
			!ft_memcmp(param->argv[i], ">>", 3)))
	{
		if (!ft_memcmp(param->argv[i], ">", 2))
			fd = open(param->argv[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0666);
		else
		{
			fd = open(param->argv[i + 1], O_RDWR | O_CREAT | O_APPEND, 0666);
			ret = 0;
			while ((ret = read(fd, &c, 1)))
				if (ret == -1)
				{
					write(1, "Couldn't read file\n", 19);
					break ;
				}
		}
		i += 2;
		if (param->argv[i])
			close(fd);
	}
	return (fd);
}

static int	set_fd(t_data *param)
{
	int		i;
	int		fd;

	i = 0;
	fd = 1;
	while (param->argv[i] && ft_memcmp(param->argv[i], ">", 2)
			&& ft_memcmp(param->argv[i], ">>", 3))
		i++;
	if (!param->argv[i])
		return (1);
	return (redirect(param, i, fd));
}

static void	copy_args1(t_data *param)
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
	free_matrix(param->argv);
	param->argv = args;
	param->argc = 0;
}

char		**check_command(char *str, t_data *param)
{
	int		fd;

	param->argc = count_args(str);
	param->argv = (char **)ft_calloc(sizeof(char *), (param->argc + 1));
	set_args(param->argv, str, param->argc);
	if (param->argv[0] && *(param->argv[0]))
	{
		fd = set_fd(param);
		copy_args1(param);
		while (param->argv[param->argc])
			(param->argc)++;
		param->ret = check_builtins(fd, param);
		if (param->ret == 127 && (param->ret = check_bin(fd, param)) == 127)
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
