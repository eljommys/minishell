/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:16:49 by marvin            #+#    #+#             */
/*   Updated: 2020/11/30 20:44:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <dirent.h>
# include <signal.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/stat.h>

void	skip_spaces(char **str);
void	free_env(char **envp);
char	*get_env(char **envp, char *env);
char	**copy_env(char **envp, int add);
int		ft_strlen_spa(char *str);
int		count_args(char *str);
void	set_args(char **argv, char *str, int argc);

void	echo_command(char **envp, char *str, int fd);
void	bash_command(char *str, char **argv, char **envp);
void	env_command(char **envp, int fd);
char	**export_command(char *str, char **envp);
char	**unset_command(char *str, char **envp);
int		check_builtins(int fd, char *start, char *str, char ***envp);
int		check_bin(int fd, char *str, char *path, char **envp);
char	**check_command(char *str, char **argv, char **envp);
char	**parser(char *str, char **argv, char **envp);

#endif
