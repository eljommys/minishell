/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 13:09:57 by marvin            #+#    #+#             */
/*   Updated: 2020/11/19 13:09:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void write_env(char **envp, char *str, int fd)
{
	char	*env;
	int		len;


	len = ft_strlen_spa(str);
	env = ft_strdup(str + 1);
	env[len - 1] = 0;
	ft_putstr_fd(get_env(envp, env), fd);
	free(env);
}

static void	write_words(char **envp, char *str, int fd)
{
	int		len;
	char	*start;
	char	str_char;
	char	*aux;

	skip_spaces(&str);
	start = str;
	while (*str && *str != '>' && *str != ';')
	{
		if (str != start)
			write(fd, " ", 1);
		len = ft_strlen_spa(str);
		if (*str == '"' || *str == '\'')
		{
			str_char = *str;
			str++;
			if (str_char == '"' && *str == '$')
			{
				aux = ft_strdup(str);
				aux[len - 2] = 0;
				write_env(envp, aux, fd);
				free(aux);
				str += len - 1; 
			}
			else
			{
				while (*str != str_char)
					write(fd, str++, 1);
				str++;
			}
		}
		else
		{
			if (*str == '$')
				write_env(envp, str, fd);
			else
				write(fd, str, len);
			str += len;
		}
		skip_spaces(&str);
	}
}

void		echo_command(char **envp, char *str, int fd)
{
	int		is_flag;

	is_flag = 0;
	str += 5;
	skip_spaces(&str);
	if (!ft_memcmp(str, "-n ", 3))
	{
		is_flag = 1;
		str += 3;
	}
	write_words(envp, str, fd);
	if (!is_flag)
		write(fd, "\n", 1);
	if (fd != 1)
		close(fd);
}
