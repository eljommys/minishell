/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 17:05:25 by marvin            #+#    #+#             */
/*   Updated: 2020/12/13 13:32:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**export_command(t_data *param, int j)
{
	int		i;
	char	**cpy;

	i = 0;
	while (param->envp[i] && ft_memcmp(param->envp[i],
			param->argv[j], ft_strlen(param->argv[j])))
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

void		export_value(t_data *param, int *i)
{
	char	**aux;
	int		j;

	if (!ft_strchr(param->argv[*i], '='))
	{
		j = 0;
		while (param->export[j] && ft_memcmp(param->export[j],
				param->argv[*i], ft_strlen(param->argv[*i])))
			j++;
		if (!param->export[j])
		{
			aux = copy_env(param->export, 1);
			aux[j] = ft_strdup(param->argv[*i]);
			aux[j + 1] = 0;
			free_matrix(param->export);
			param->export = aux;
		}
		(*i)++;
	}
	else
	{
		param->envp = export_command(param, *i);
		
		*i += param->argv[*i + 1] ? 2 : 1;
	}
}

int			check_export_error(char **argv, int *i)
{
	int j;

	j = 0;
	while (ft_isalnum(argv[*i][j]) || argv[*i][j] == '_' ||
			argv[*i][j] == '#' || argv[*i][j] == '=' || argv[*i][j] == '$')
		j++;
	if (ft_isdigit(argv[*i][0]) || argv[*i][j])
	{
		if (ft_strchr(argv[*i], '='))
		{
			ft_putstrs_fd("bash: ", argv[0], ": `", 2);
			ft_putstrs_fd(argv[*i], argv[(*i) + 1],
				"': not a valid identifier\n", 2);
			(*i)++;
		}
		else
		{
			ft_putstrs_fd("bash: ", argv[0], ": `", 2);
			ft_putstrs_fd(argv[*i], "': not a valid identifier\n", 0, 2);
		}
		(*i)++;
		return (1);
	}
	return (0);
}

static void	put_envp(char **aux, int fd)
{
	int i;

	i = -1;
	while (aux[++i])
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstrlen_fd(aux[i], ft_strlen_char(aux[i], '=') + 1, fd);
		if (ft_strchr(aux[i], '='))
			ft_putstrs_fd("\"", ft_strchr(aux[i], '=') + 1, "\"", fd);
		write(fd, "\n", 1);
	}
	free_matrix(aux);
}

void		sort_envp(char **envp, int fd, char c)
{
	int		i;
	int		len;
	char	**aux;
	char	*tmp;

	aux = copy_env(envp, 0);
	i = 0;
	while (aux[i] && aux[i + 1])
	{
		len = (ft_strlen_char(aux[i], c) > ft_strlen_char(aux[i + 1], c))
				? ft_strlen_char(aux[i], c) : ft_strlen_char(aux[i + 1], c);
		if (ft_memcmp(aux[i], aux[i + 1], len) > 0)
		{
			tmp = aux[i];
			aux[i] = aux[i + 1];
			aux[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
	put_envp(aux, fd);
}
