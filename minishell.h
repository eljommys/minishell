/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:16:49 by marvin            #+#    #+#             */
/*   Updated: 2020/12/02 22:01:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <dirent.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/stat.h>

typedef struct		s_data{
	int		argc;
	char	**argv;
	char	**envp;
	int		ret;
}					t_data;

void	skip_spaces(char **str);
void	free_env(char **envp);
char	*get_env(char **envp, char *env);
char	**copy_env(char **envp, int add);
int		ft_strlen_spa(char *str);
int		ft_strlen_pipe(char *str);
int		ft_strlen_char(char *str, char c);
int		count_args(char *str);
void	set_args(char **argv, char *str, int argc);

void	bash_command(t_data *param);
void	env_command(t_data *param, int fd);
char	**export_command(t_data *param);
char	**unset_command(t_data *param);
void	exit_command(char *str, t_data *param);
int		check_builtins(int fd, char *start, t_data *param);
int		check_bin(int fd, t_data *param);
char	**check_command(char *str, t_data *param);
char	**parser(char *str, t_data *param);

#endif
