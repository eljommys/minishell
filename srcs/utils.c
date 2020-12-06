/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 15:41:14 by marvin            #+#    #+#             */
/*   Updated: 2020/12/06 10:19:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_sig_handler(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
}

void	skip_spaces(char **str)
{
	while (**str == ' ' || (9 <= **str && **str <= 13))
		(*str)++;
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}

char	*get_env(char **envp, char *env)
{
	int		i;
	int		len;
	char	*tmp;

	env = ft_strjoin(env, "=");
	len = strlen(env);
	i = 0;
	while (envp[i] && ft_memcmp(env, envp[i], len))
		i++;
	if (envp[i])
		tmp = envp[i] + len;
	else
		tmp = 0;
	free(env);
	return (tmp);
}

char	**copy_env(char **envp, int add)
{
	int		len;
	int		i;
	char	**cpy;

	len = 0;
	while (envp[len])
		len++;
	if (!(cpy = (char **)ft_calloc(sizeof(char *), (len + add + 1))))
		return (0);
	i = -1;
	while (++i < len)
		cpy[i] = ft_strdup(envp[i]);
	return (cpy);
}
