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

void	echo_command(char *str);
void	pwd_command(void);
void	exit_command(char *str);
void	bash_command(char *str);
void	cd_command(char *str);
