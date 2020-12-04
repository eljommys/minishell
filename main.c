/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:16:03 by marvin            #+#    #+#             */
/*   Updated: 2020/12/04 20:04:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*relative_path(char *cwd, char **envp)
{
	char	*home;
	char	*path;

	home = get_env(envp, "HOME");
	if (ft_memcmp(cwd, home, ft_strlen(home)))
		path = ft_strdup(cwd);
	else
		path = ft_strjoin("~", cwd + ft_strlen(home));
	return (path);
}

void		sig_handler(int sig)
{
	char *cwd;
	char buff[4097];

	if (sig == SIGINT)
	{
	cwd = getcwd(buff, 4096);
	write(1, "\n", 1);
	write(1, "\033[1;31mminishell@PARMART-JSERRAN\033[0;0m", 38);
	ft_putstrs_fd(":\033[1;34m", cwd, "\033[0;0m$ ", 1);
	}
	else if (sig == SIGQUIT)
		exit(0);
}

void		child_sig_handler(int sig)
{
	if (sig == SIGINT)
		exit(0);
}

int			main(int argc, char **argv, char **envp)
{
	char	*cwd;
	char	buff[4097];
	t_data	*param;
	int		sample;

	param = (t_data *)malloc(sizeof(t_data));
	param->envp = copy_env(envp, 0);
	param->argv = argv;
	param->ret = 0;
	param->child = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	while (1)
	{
		param->str = 0;
		cwd = relative_path(getcwd(buff, 4096), param->envp);
		write(1, "\r\033[1;31mminishell@PARMART-JSERRAN\033[0;0m", 39);
		ft_putstrs_fd(":\033[1;34m", cwd, "\033[0;0m$ ", 1);
		free(cwd);
		if (!(sample = get_next_line(1, &(param->str))) && !ft_strlen(param->str))
		{
				free(param->str);
				ft_putstr_fd("\nlogout\n", 1);
				exit(0);
		}
		if (sample)
			envp = parser(param->str, param);
	}
}
