/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:16:03 by marvin            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2020/12/05 12:47:01 by marvin           ###   ########.fr       */
=======
/*   Updated: 2020/12/05 12:46:48 by marvin           ###   ########.fr       */
>>>>>>> f9d2ed16f2e6e3915f43fe8e1b00ab93a129f2a6
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put_prompt(char **envp)
{
	char	*home;
	char	*path;
	char	*cwd;
	char	buff[4097];

	home = get_env(envp, "HOME");
	cwd = getcwd(buff, 4096);
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
	char *cwd;
	char buff[4097];

	if (sig == SIGINT)
	{
		cwd = getcwd(buff, 4096);
		write(1, "\n", 1);
		write(1, "\r\033[1;31mminishell@PARMART-JSERRAN\033[0;0m", 39);
		ft_putstrs_fd(":\033[1;34m", cwd, "\033[0;0m$ ", 1);
		signal(SIGINT, sig_handler);
	}
	else if (sig == SIGQUIT)
		exit(0);
}

static void	init_param(t_data **param, char **argv, char **envp)
{
	(*param) = (t_data *)malloc(sizeof(t_data));
	(*param)->envp = copy_env(envp, 0);
	(*param)->argv = argv;
	(*param)->ret = 0;
	(*param)->child = 0;
}

int			main(int argc, char **argv, char **envp)
{
	t_data	*param;
	int		input;

	if (argc != 1)
		return (1);
	init_param(&param, argv, envp);
	signal(SIGQUIT, sig_handler);
	while (1)
	{
		put_prompt(param->envp);
		signal(SIGINT, sig_handler);
		param->str = 0;
		if (!(input = get_next_line(1, &(param->str)))
				&& !ft_strlen(param->str))
		{
			free(param->str);
			ft_putstr_fd("\nlogout\n", 1);
			exit(0);
		}
		else if (input)
			envp = parser(param->str, param);
	}
	return (0);
}
