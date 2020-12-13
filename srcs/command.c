/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 18:22:40 by marvin            #+#    #+#             */
/*   Updated: 2020/12/13 13:46:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect(t_data *param, int i, int fd)
{
	int		ret;
	char	c;

	while (param->argv[i])
	{
		if (!ft_memcmp(param->argv[i], ">", 2))
			fd = open(param->argv[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0666);
		else if (!ft_memcmp(param->argv[i], ">>", 3))
		{
			fd = open(param->argv[i + 1], O_RDWR | O_CREAT | O_APPEND, 0666);
			ret = 0;
			while ((ret = read(fd, &c, 1)))
				if (ret == -1)
				{
					write(2, "Couldn't read file\n", 19);
					break ;
				}
		}
		i++;
		 if (param->argv[i] &&
		 	(!ft_memcmp(param->argv[i], ">>", 3) ||
			 !ft_memcmp(param->argv[i], ">", 2)))
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

static int count_redir(t_data *param)
{
	int	count;
	int	i;

	i = -1;
	count = 0;
	while (++i < param->argc)
	{
		if (!ft_memcmp(param->argv[i], ">", 2) ||
			!ft_memcmp(param->argv[i], ">>", 3))
		{
			count++;
			i++;
		}
	}
	return(count);
}

static void	copy_args1(t_data *param)
{
	int		i;
	int		j;
	char	**args;

	param->argc -= count_redir(param) * 2;
	args = (char **)ft_calloc(sizeof(char *), param->argc + 1);
	i = 0;
	j = 0;
	while (j < param->argc)
	{
		if (!ft_memcmp(param->argv[i], ">", 2) ||
			!ft_memcmp(param->argv[i], ">>", 3))
			i += 2;
		else
			args[j++] = ft_strdup(param->argv[i++]);
	}
	free_matrix(param->argv);
	param->argv = args;
}

char		**check_command(char *str, t_data *param)
{
	int		fd;
	int		i;

	if (param->argv[0] && *(param->argv[0]))
	{
		fd = set_fd(param);
		copy_args1(param);
		param->ret = check_builtins(fd, param);
		if (param->ret == 127 && (param->ret = check_bin(fd, param)) == 127)
		{
			ft_putstrs_fd(0, str, ": command not found.\n", 2);
			param->ret = 127;
		}
		if (fd != 1)
			close(fd);
	}
	return (param->envp);
}
