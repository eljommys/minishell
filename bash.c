/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 19:50:12 by marvin            #+#    #+#             */
/*   Updated: 2020/11/17 19:50:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void skip_spaces(char **str)
{
	while (**str == ' ')
		(*str)++;
}

static void set_path(char *str, char **path)
{
	int		i;
	int		len;
	char	*filename;
	char	*new;
	char	*aux;

	new = ft_strdup(*path);
	len = ft_strlen(*path);
	i = 0;
	if (!ft_memcmp(str, "/", 1))
		*path = ft_strdup(str);
	else
	{
		while (!ft_memcmp(str + i, "../", 3))
			i += 3;
		filename = ft_strdup(str + i);
		i /= 3;
		while (i-- > 0)
		{
			while (new[len] != '/')
				len--;
			len--;
		}
		new[len + 1] = 0;
		aux = ft_strjoin(new, "/");
		free(new);
		new = ft_strjoin(aux, filename);
		free(aux);
		free(filename);
		*path = new;
	}
}

void		bash_command(char *str)
{
	char	**argv;
	char	**env;
	char	buff[4097];
	char	*path;
	int		status[2];

	argv = (char **)ft_calloc(1, sizeof(char *));
	env = (char **)ft_calloc(1, sizeof(char *));
	skip_spaces(&str);
	if (ft_memcmp(str, "/", 1))
		str += (!ft_memcmp(str, "./", 2)) ? 2 : 3;
	path = getcwd(buff, 4096);
	set_path(str, &path);
	status[0] = 0;
	if (!fork() && execve(path, argv, env) == -1)
	{
		write(1, "Wrong file or directory\n", 24);
		status[0] = 1;
	}
	else
		wait(&status[1]);
	free(argv);
	free(env);
	free(path);
	if (status[0])
		exit(0);
}
