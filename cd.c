/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 13:41:47 by marvin            #+#    #+#             */
/*   Updated: 2020/11/20 13:41:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_command(char *str)
{
	str += 3;
	char	buff[4097];
	char	*path;

	path = getcwd(buff, 4096);
	set_path(str, &path);
	chdir(path);
	free(path);
}
