/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrs_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 17:41:19 by marvin            #+#    #+#             */
/*   Updated: 2020/11/30 17:41:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstrs_fd(char *before, char *str, char *after, int fd)
{
	if (!str)
		return;
	write(fd, before, ft_strlen(before));
	write(fd, str, ft_strlen(str));
	write(fd, after, ft_strlen(after));
}