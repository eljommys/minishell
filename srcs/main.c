/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:16:03 by marvin            #+#    #+#             */
/*   Updated: 2020/12/10 09:13:33 by marvin           ###   ########.fr       */
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

static void	init_param(t_data **param, char **argv, char **envp)
{
	(*param) = (t_data *)malloc(sizeof(t_data));
	(*param)->envp = copy_env(envp, 0);
	(*param)->export = (char **)ft_calloc(sizeof(char *), 1);
	(*param)->argv = argv;
	(*param)->ret = 0;
	(*param)->child = 0;
}

static void		ft_stty()
{
	pid_t	child;
	char	*args[5];

	child = fork();
	if (child < 0)
		exit (1);
	if (!child)
	{
		args[0] = "/bin/stty";
		args[1] = "discard";
		args[2] = "\4";
		args[3] = NULL;
		execve(args[0], args, NULL);
		exit (1);
	}
	if (child > 0)
		wait(NULL);
}

int			check_char(char c)
{
	printf("%c\n", c);
	if (c == 3 || c == 4)
		return ((int)c);
	else if (c == '\n')
		return (1);
	return (0);
}

void		check_key(int key, t_data *param)
{
	if (key == 4 && !ft_strlen(param->str))
		exit_command(param);
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
	char	c;
	int		key;

	if (argc != 1)
		return (1);
	init_param(&param, argv, envp);
	signal(SIGQUIT, sig_handler);
	signal(SIGINT, sig_handler);
	ft_stty();
	while (1)
	{
		put_prompt(param->envp);
		param->str = 0;
		while (read(0, &c, 1))
		{
			if ((key = check_char(c)))
			{
				printf("a\n");
				break ;
			}
			add_char(&(param->str), c);
		}
		if (key > 1)
		{
			printf("b\n");
			check_key(key, param);
		}
		else
			parser(param);
	}
	return (0);
}
