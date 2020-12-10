/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:16:03 by marvin            #+#    #+#             */
/*   Updated: 2020/12/10 12:29:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		put_prompt(char **envp)
{
	char	*home;
	char	*path;
	char	cwd[4097];

	home = get_env(envp, "HOME");
	getcwd(cwd, 4096);
	if (ft_memcmp(cwd, home, ft_strlen(home)))
		path = ft_strdup(cwd);
	else
		path = ft_strjoin("~", cwd + ft_strlen(home));
	write(1, "\033[1;31mminishell@PARMART-JSERRAN\033[0;0m", 38);
	ft_putstrs_fd(":\033[1;34m", path, "\033[0;0m$ ", 1);
	free(path);
}

static void	sig_handler(int sig)
{
	char cwd[4097];

	if (sig == SIGINT)
	{
		getcwd(cwd, 4096);
		write(1, "\n", 1);
		write(1, "\r\033[1;31mminishell@PARMART-JSERRAN\033[0;0m", 39);
		ft_putstrs_fd(":\033[1;34m", cwd, "\033[0;0m$ ", 1);
	}
}

static void	init_param(t_data **param, char **argv, char **envp, int *ret_len)
{
	(*param) = (t_data *)malloc(sizeof(t_data));
	(*param)->envp = copy_env(envp, 0);
	(*param)->export = (char **)ft_calloc(sizeof(char *), 1);
	(*param)->argv = argv;
	(*param)->ret = 0;
	(*param)->str = 0;
	(*param)->child = 0;
	ret_len[0] = 1;
}

void		add_char(char **str, char c)
{
	char	*aux;

	aux = ft_calloc(sizeof(char), ft_strlen(*str) + 2);
	ft_memcpy(aux, *str, ft_strlen(*str));
	aux[ft_strlen(aux)] = c;
	if (*str)
		free(*str);
	*str = aux;
}

int			main(int argc, char **argv, char **envp)
{
	t_data	*param;
	int		ret_len[2];
	char	c;

	if (argc != 1)
		return (1);
	init_param(&param, argv, envp, ret_len);
	signal(SIGQUIT, sig_handler);
	while (1)
	{
		if (ret_len[0])
			put_prompt(param->envp);
		signal(SIGINT, sig_handler);
		while ((ret_len[0] = read(1, &c, 1)) && c != '\n')
			add_char(&(param->str), c);
		ret_len[1] = (int)ft_strlen(param->str);
		if (c == '\n')
			parser(param);
		if (!ret_len[0] && !ret_len[1])
		{
			ft_putstr_fd("\nlogout\n", 1);
			exit(0);
		}
	}
	return (0);
}
