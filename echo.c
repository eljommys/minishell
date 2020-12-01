/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 13:09:57 by marvin            #+#    #+#             */
/*   Updated: 2020/12/01 13:40:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static void	write_env(char **envp, char *str, int fd, int len)
{
	char	*env;

	env = ft_strdup(str + 1);
	env[len - 1] = 0;
	ft_putstr_fd(get_env(envp, env), fd);
	free(env);
}

static char	*check_quotes(char **envp, char *str, int fd, int len)
{
	char	str_char;
	char	*aux;

	str_char = *str;
	str++;
	if (str_char == '"' && *str == '$')
	{
		aux = ft_strldup(str, len - 2);
		write_env(envp, aux, fd, len);
		free(aux);
		str += len - 1;
	}
	else
	{
		while (*str != str_char)
			write(fd, str++, 1);
		str++;
	}
	return (str);
}

static void	write_words(char **envp, char *str, int fd)
{
	int		len;
	char	*start;

	skip_spaces(&str);
	start = str;
	while (*str && *str != '>' && *str != ';')
	{
		if (str != start)
			write(fd, " ", 1);
		len = ft_strlen_spa(str);
		if (*str == '"' || *str == '\'')
			str = check_quotes(envp, str, fd, len);
		else
		{
			if (*str == '$')
				write_env(envp, str, fd, len);
			else
				write(fd, str, len);
			str += len;
		}
		skip_spaces(&str);
	}
}*/

static void		write_words(char **argv, int fd)
{
	int i;

	i = 1;
	while (argv[i])
	{
		ft_putstr_fd(argv[i], fd);
		i++;
	}
}

void		echo_command(t_data *param, int fd)
{
	int	flag;

	flag = 0;
	if (!ft_memcmp(param->argv[1], "-n", 3))
		flag = 1;
	write_words(param->argv + flag, fd);
	if (!flag)
		write(fd, "\n", 1);
	if (fd != 1)
		close(fd);
}
