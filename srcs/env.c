/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 15:42:40 by marvin            #+#    #+#             */
/*   Updated: 2020/12/08 15:08:39 by marvin           ###   ########.fr       */
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
	if (!(cpy = (char **)ft_calloc(sizeof(char *), len)))
		return (NULL);
	j = -1;
	while (++j < i)
		cpy[j] = ft_strdup(envp[j]);
	i++;
	while (envp[i])
		cpy[j++] = ft_strdup(envp[i++]);
	free_matrix(envp);
	return (cpy);
}

char		**unset_command(t_data *param, int j)
{
	int		i;
	int		len;
	char	*env;
	char	**cpy;

	if (param->argc < 2)
		return (param->envp);
	len = strlen(param->argv[j]);
	env = ft_strjoin(param->argv[j], "=");
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

char		**export_command(t_data *param, int j)
{
	int		i;
	char	**cpy;

	i = 0;
	while (param->envp[i] &&
		ft_memcmp(param->envp[i], param->argv[j], ft_strlen(param->argv[j])))
		i++;
	if (!param->envp[i])
	{
		cpy = copy_env(param->envp, 1);
		cpy[i] = ft_strjoin(param->argv[j], param->argv[j + 1]);
		free_matrix(param->envp);
	}
	else
	{
		cpy = param->envp;
		free(param->envp[i]);
		param->envp[i] = ft_strjoin(param->argv[j], param->argv[j + 1]);
	}
	return (cpy);
}

static void	sort_envp(char **envp, int fd)
{
	int		i;
	int		len;
	char	*tmp;
	char	**aux;

	aux = copy_env(envp, 0);
	i = 0;
	while (aux[i])
	{
		len = (ft_strlen_char(aux[i], '=') > ft_strlen_char(aux[i + 1], '='))
			? ft_strlen_char(aux[i], '=') : ft_strlen_char(aux[i + 1], '=');
		if (aux[i + 1] && ft_memcmp(aux[i], aux[i + 1], len) > 0)
		{
			tmp = aux[i];
			aux[i] = aux [i + 1];
			aux [i + 1] = tmp;
			i = -1;
		}
		i++;
	}
	i = -1;
	while (aux[++i])
		ft_putstrs_fd("declare -x ", aux[i], "\n", fd);
	free_matrix(aux);
}

char		**multiple_env(t_data *param, int fd)
{
	int		i;
	int		j;
	char	**aux;

	if (!ft_memcmp(param->argv[0], "export", 7) && param->argc == 1)
	{
		sort_envp(param->envp, fd);
		if (param->export)
			sort_envp(param->export, fd);
	}
	i = 1;
	while (param->argv[i])
	{
		if (!ft_memcmp(param->argv[0], "export", 7))
		{
			if ((int)ft_strlen(param->argv[i]) == ft_strlen_char(param->argv[i], '='))
			{
				j = 0;
				while (param->export[j])
					j++;
				aux = copy_env(param->export, 1);
				aux[j] = ft_strdup(param->export[j]);
				free_matrix(param->export);
				param->export = aux;
				free_matrix(aux);
				i++;
			}
			else
			{
				param->envp = export_command(param, i);
				i += 2;
			}
		}
		else if (!ft_memcmp(param->argv[0], "unset", 6))
			param->envp = unset_command(param, i++);
	}
	return (param->envp);
}

void		env_command(t_data *param, int fd)
{
	int	i;

	i = 0;
	if (param->argc != 1)
	{
		ft_putstrs_fd("env: ‘", param->argv[1], "’: Permission denied\n", 1);
		return ;
	}
	while (param->envp[i])
		ft_putstrs_fd(param->envp[i++], "\n", 0, fd);
}
