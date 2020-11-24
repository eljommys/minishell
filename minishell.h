/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:16:49 by marvin            #+#    #+#             */
/*   Updated: 2020/11/16 15:16:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#endif

#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>

void	skip_spaces(char **str);
void	free_env(char **envp);
char	*get_env(char **envp, char *env);
char	**copy_env(char **envp, int add);
int		ft_strlen_spa(char *str);

void	echo_command(char **envp, char *str, int fd);
void	pwd_command(int fd);
void	cd_command(char **envp, char *str);
void	exit_command(char *str, char **envp);
void	bash_command(char *str, char **argv, char **envp);
void	env_command(char **envp, int fd);
char	**export_command(char *str, char **envp);
char	**unset_command(char *str, char **envp);
void	check_bin(char *str, char **envp);
