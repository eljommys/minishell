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

/*
**	librerias de prueba (eliminar en la version final)
*/

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
void	set_path(char *str, char **path);
char	**copy_env(char **envp, int add);

void	echo_command(char *str, int fd);
void	pwd_command(int fd);
void	ls_command(int fd);
void	cd_command(char *str);
void	exit_command(char *str, char **envp);
void	env_command(char **envp, int fd);
void	bash_command(char *str, char **argv, char **envp);
char	**export_command(char *str, char **envp);
char	**unset_command(char *str, char **envp);
