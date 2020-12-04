/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 14:12:39 by marvin            #+#    #+#             */
/*   Updated: 2020/12/04 14:51:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipe_son(int *flag, int *fds, char *str, t_data *param)
{
	int		i;
	char	*command;

	if (!fork())
	{
		if (!flag[0])
			dup2(fds[0], 0);
		if (!flag[1])
			dup2(fds[3], 1);
		i = 0;
		while (i < 4)
			close(fds[i++]);
		command = ft_strldup(str, ft_strlen_pipe(str));
		check_command(command, param);
		exit(param->ret);
	}
}

static int	check_pipe(int *fds, char *str, t_data *param)
{
	int		i;
	int		*flag;

	i = 0;
	flag = (int *)malloc(sizeof(int) * 2);
	flag[0] = 1;
	flag[1] = 0;
	while (!flag[1])
	{
		flag[1] = (!str[ft_strlen_pipe(str)]) ? 1 : 0;
		pipe_son(flag, fds, str, param);
		i++;
		str += ft_strlen_pipe(str) + 1;
		flag[0] = 0;
		close(fds[0]);
		close(fds[1]);
		fds[0] = fds[2];
		fds[1] = fds[3];
		pipe(fds + 2);
	}
	free(flag);
	return (i);
}

static int	change_env(int i, char **str, t_data *param)
{
	int		len;
	char	*bef;
	char	*aft;
	char	*env;
	char	*aux;

	//printf("str_inicio = ->%s<-\n", *str);
		//len[1] = 0;
		/*if ((*str)[i] == '"')
		{
			len[0] = ft_strlen_char(*str + i + 1, '"');
			len[1] = 2;
		}
		else
			len[0] = (ft_strlen_char(*str + i + 1, ':') < ft_strlen_spa(*str + i + 1)) ?
			ft_strlen_char(*str + i + 1, ':') + 1 : ft_strlen_spa(*str + i + 1) + 1;*/
	len = ft_strlen_spa(*str + i + 1) + 1;
	bef = ft_strldup(*str, i);
	//printf("len = %d\n", len);
	aux = ft_strldup(*str + i + 1, len - 1);
	env = (!ft_memcmp(aux, "?", 2)) ? ft_itoa(param->ret) : 0;
	aft = ft_strdup(*str + i + len);
	//printf("aux = %s\n", aux);
	env = (!env) ? ft_strdup(get_env(param->envp, aux)) : env;
	//printf("env = %s\n", env);
	free(aux);
		//aux = ft_strjoin("\"", env);
		//free(env);
		//env = ft_strjoin(aux, "\"");
		//free(aux);
	len = ft_strlen(env);
	aux = ft_strjoin(bef, env);
	free(bef);
	free(env);
	free(*str);
	*str = ft_strjoin(aux, aft);
	//printf("str_final = ->%s<-\n", *str);
	free(aux);
	free(aft);
	//printf("len_final = %d\n", len);
	return (len);
}

static void	check_env(char **str, t_data *param)
{
	int i;
	char *cpy;

	cpy = *str;
	i = 0;
	while ((*str) && (*str)[i])
	{
		if ((*str)[i] == '\'')
		{
			i++;
			while ((*str)[i] && (*str)[i] != '\'')
				i++;
			if (!(*str)[i])
			{
				ft_putstr_fd("Non finished quotes\n", 1);
				break;
			}
			i++;
		}
		if ((*str)[i] == '$')
			i += change_env(i, str, param) - 1;
		i++;
	}
}

char		**parser(char *str, t_data *param)
{
	int		fds[4];
	int		std_out;
	int		status;
	int		i;
	int		j;

	if (!str || !ft_memcmp(str, ";", 2))
	{
		if (str)
			ft_putstr_fd("-bash; syntax error near unexpected token `;'\n", 1);
		free(str);
		return (param->envp);
	}
	param->com = ft_split(str, ';');
	j = 0;
	while (param->com[j])
	{
		check_env(&(param->com[j]), param);
		std_out = dup(0);
		printf("comando = ->%s<-\n", param->com[j]);
		if (param->com[j] && !param->com[j][ft_strlen_pipe(param->com[j])])
			param->envp = check_command(param->com[j], param);
		else if (param->com[j])
		{
			pipe(fds);
			pipe(fds + 2);
			i = check_pipe(fds, param->com[j], param);
			while (i-- > 0)
				wait(&param->ret);
			param->ret /= 256;
			//free(param->com[j]);
			while (i < 4)
				close(fds[i++]);
		}
		dup2(std_out, 0);
		j++;
	}
	free(param->str);
	free_env(param->com);
	return (param->envp);
}
