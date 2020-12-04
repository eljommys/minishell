/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 15:42:40 by marvin            #+#    #+#             */
/*   Updated: 2020/12/04 12:41:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**erase_env(char **envp, int i)
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

char		**unset_command(t_data *param)
{
	int		i;
	int		len;
	char	*env;
	char	**cpy;

	len = strlen(param->argv[1]);
	env = ft_strjoin(param->argv[1], "=");
	i = 0;
	while (param->envp[i] && ft_memcmp(env, param->envp[i], len + 1))
		i++;
	if (param->envp[i])
		cpy = erase_env(param->envp, i);
	else
		cpy = param->envp;
	free(env);
	return (cpy);
}

char		**export_command(t_data *param)
{
	int		i;
	char	**cpy;
	char	*aux;
	char	*env;

	env = ft_strdup(param->argv[1]);
	i = 1;
	while (param->argv[++i] && (*(param->argv[i]) == ':' || param->argc <= 4))
	{
		aux = ft_strjoin(env, param->argv[i]);
		free(env);
		env = aux;
	}
	i = 0;
	while (param->envp[i] &&
		ft_memcmp(param->envp[i], env, ft_strlen_char(env, '=') + 1))
		i++;
	if (!param->envp[i])
	{
		cpy = copy_env(param->envp, 1);
		cpy[i] = env;
		free_env(param->envp);
	}
	else
	{
		cpy = param->envp;
		free(param->envp[i]);
		param->envp[i] = env;
		//env = ft_strldup(param->envp[i], ft_strlen_char(param->envp[i], '='));
	}
	return (cpy);
}

void		env_command(t_data *param, int fd)
{
	int	i;

	i = 0;
	if (param->argc != 1)
	{
		ft_putstr_fd("Wrong number arguments in 'env'!\n", 1);
		return ;
	}
	while (param->envp[i])
	{
		ft_putstr_fd(param->envp[i++], fd);
		write(fd, "\n", 1);
	}
}
