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
		if (!ft_memcmp(str, "./", 2))
			str += 2;
		else
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

	argv = (char **)ft_calloc(1, sizeof(char *));
	env = (char **)ft_calloc(1, sizeof(char *));
	str += (!ft_memcmp(str, "bash ", 5)) ? 5 : 2;
	skip_spaces(&str);
	printf("str = %s\n", str);
	path = getcwd(buff, 4096);
	set_path(str, &path);
	printf("path = %s\n", path);
	if (execve(path, argv, env) == -1)
		write(1, "Wrong file or directory\n", 24);
	free(argv);
	free(env);
	free(path);
}
