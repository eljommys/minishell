/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 21:04:43 by marvin            #+#    #+#             */
/*   Updated: 2020/12/05 09:50:52 by parmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_strncpy1(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

static char	*ft_strjoin1(char *s1, char *s2)
{
	int		lenstr;
	int		lens1;
	int		lens2;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	lenstr = 0;
	lens1 = -1;
	while (s1[++lens1])
		lenstr++;
	lens2 = -1;
	while (s2[++lens2])
		lenstr++;
	str = (char *)malloc(lenstr + 1);
	if (!str)
		return (NULL);
	ft_strncpy1(str, s1, lens1 + 1);
	ft_strlcat(str, s2, lenstr + 1);
	free(s1);
	return (str);
}

static char	*ft_strchr1(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (c == 0)
		return ((char *)s);
	return (0);
}

static int	copy_line(char **remind, char **line, int fd)
{
	int		i;
	char	*ptr;

	i = 0;
	while (remind[fd][i] != '\n' && remind[fd][i] != '\0')
		i++;
	if (!(*line = (char *)malloc(i + 1)))
		return (-1);
	ft_strncpy1(*line, remind[fd], i + 1);
	ptr = ft_strchr1(remind[fd], '\n');
	if (ptr)
	{
		ptr = ft_strdup(ptr + 1);
		free(remind[fd]);
		remind[fd] = ptr;
		return (1);
	}
	free(remind[fd]);
	remind[fd] = NULL;
	return (0);
}

int			get_next_line(int fd, char **line)
{
	char		*buffer;
	static char	*remind[4096];
	int			nbytes;

	buffer = (char *)malloc(32 + 1);
	if (!line || fd < 0 || !buffer || 32 <= 0)
		return (-1);
	while ((nbytes = read(fd, buffer, 32)) && nbytes > 0)
	{
		buffer[nbytes] = '\0';
		if (!remind[fd])
			remind[fd] = ft_strdup(buffer);
		else
			remind[fd] = ft_strjoin1(remind[fd], buffer);
		if (ft_strchr1(remind[fd], '\n'))
			break ;
	}
	free(buffer);
	if (nbytes < 0)
		return (-1);
	else if (nbytes > 0 || (nbytes == 0 && remind[fd]))
		return (copy_line(remind, line, fd));
	*line = ft_strdup("");
	return (0);
}
