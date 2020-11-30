/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 15:42:40 by marvin            #+#    #+#             */
/*   Updated: 2020/11/30 17:15:00 by parmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**erase_elm(char **envp, int i)
{
	int		j;
	int		len;
	char	**cpy;

	len = 0;
	while (envp[len])
		len++;
	if (!(cpy = (char **)malloc(sizeof(char *) * len)))
		return (0);
	j = -1;
	while (++j < i)
		cpy[j] = ft_strdup(envp[j]);
	i++;
	while (envp[i])
		cpy[j++] = ft_strdup(envp[i++]);
	cpy[j] = 0;
	free_env(envp);
	return (cpy);
}

char		**unset_command(char *str, char **envp)
{
	int		i;
	int		var_len;
	char	*var_search;
	char	**cpy;

	str += 6;
	skip_spaces(&str);
	var_len = strlen(str);
	var_search = ft_strjoin(str, "=");
	i = 0;
	while (envp[i] && ft_memcmp(var_search, envp[i], var_len + 1))
		i++;
	cpy = envp;
	if (envp[i])
		cpy = erase_elm(envp, i);
	free(var_search);
	return (cpy);
}

char		**export_command(char *str, char **envp)
{
	int		i;
	char	**cpy;

	str += 7;
	skip_spaces(&str);
	cpy = copy_env(envp, 1);
	free_env(envp);
	i = 0;
	while (cpy[i])
		i++;
	cpy[i] = ft_strdup(str);
	cpy[i + 1] = 0;
	return (cpy);
}

void		env_command(char **envp, int fd)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_putstr_fd(envp[i++], fd);
		write(fd, "\n", 1);
	}
}
