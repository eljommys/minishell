/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:16:03 by marvin            #+#    #+#             */
/*   Updated: 2020/12/03 11:57:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_char(char **str, char c)
{
	char	*new;
	int		len;
	int		i;

	if (!(*str))
	{
		if (!(*str = (char *)ft_calloc(sizeof(char), 2)))
			return (-1);
		(*str)[0] = c;
		return (0);
	}
	len = ft_strlen(*str);
	if (!(new = (char *)ft_calloc(sizeof(char), len + 2)))
		return (-1);
	i = -1;
	while (++i < len)
		new[i] = (*str)[i];
	new[i] = c;
	if (len)
		free(*str);
	*str = new;
	return (0);
}

static char	*relative_path(char *cwd, char **envp)
{
	char	*home;
	char	*path;

	home = get_env(envp, "HOME");
	if (ft_memcmp(cwd, home, ft_strlen(home)))
		path = ft_strdup(cwd);
	else
		path = ft_strjoin("~", cwd + ft_strlen(home));
	return (path);
}

int			main(int argc, char **argv, char **envp)
{
	char	c;
	char	*str;
	char	*cwd;
	char	buff[4097];
	t_data	*param;

	param = (t_data *)malloc(sizeof(t_data));
	param->envp = copy_env(envp, 0);
	param->argv = argv;
	param->ret = 0;
	while (1)
	{
		str = 0;
		cwd = relative_path(getcwd(buff, 4096), param->envp);
		write(1, "\033[1;31mminishell@PARMART-JSERRAN\033[0;0m", 38);
		ft_putstrs_fd(":\033[1;34m", cwd, "\033[0;0m$ ", 1);
		free(cwd);
		while (1)
		{
			if (read(1, &c, 1) == 1 && c == '\n')
				break ;
			if (add_char(&str, c))
				return (-1);
		}
		envp = parser(str, param);
	}
}
