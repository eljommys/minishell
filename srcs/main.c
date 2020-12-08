/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:16:03 by marvin            #+#    #+#             */
/*   Updated: 2020/12/08 20:50:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put_prompt(char **envp)
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

static void	init_param(t_data **param, char **argv, char **envp)
{
	(*param) = (t_data *)malloc(sizeof(t_data));
	(*param)->envp = copy_env(envp, 0);
	(*param)->export = (char **)ft_calloc(sizeof(char *), 1);
	(*param)->argv = argv;
	(*param)->ret = 0;
	(*param)->child = 0;
}

int			main(int argc, char **argv, char **envp)
{
	t_data	*param;

	if (argc != 1)
		return (1);
	init_param(&param, argv, envp);
	signal(SIGQUIT, sig_handler);
	while (1)
	{
		put_prompt(param->envp);
		signal(SIGINT, sig_handler);
		param->str = 0;
		if ((get_next_line(0, &(param->str)) <= 0))
		{
			ft_putstr_fd("\nlogout\n", 1);
			exit(0);
		}
		parser(param);
	}
	return (0);
}
