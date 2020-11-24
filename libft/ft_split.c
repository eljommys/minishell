/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 08:53:03 by jserrano          #+#    #+#             */
/*   Updated: 2020/07/11 10:52:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

static int	number_str(char *s, char c)
{
	int	n_str;
	int	check;
	int i;

	n_str = 0;
	check = 0;
	i = -1;
	if (s[0] == '\0')
		return (0);
	while (s[++i] != '\0')
	{
		if (s[i] == c)
			check = 0;
		else if (check++ == 0)
			n_str++;
	}
	return (n_str);
}

static char	**free_ptr(char **ptr, int i)
{
	while (--i >= 0)
		free(ptr[i]);
	free(ptr);
	return (ptr);
}

static char	**pass_values(char **ptr, char *s, char c, int n_str)
{
	int	i;
	int j;
	int	k;

	i = -1;
	j = 0;
	while (j < n_str)
	{
		if (s[++i] != c)
		{
			k = 0;
			while (s[i] != c && s[i] != '\0')
				ptr[j][k++] = s[i++];
			ptr[j][k] = '\0';
			j++;
		}
	}
	ptr[j] = NULL;
	return (ptr);
}

static char	**set_ptr(char **ptr, char *s, char c, int n_str)
{
	int	i;
	int	j;
	int size;

	i = -1;
	j = 0;
	while (j < n_str)
	{
		if (s[++i] != c)
		{
			size = 0;
			while (s[i + size] != c && s[i + size] != '\0')
				size++;
			ptr[j] = (char *)malloc(size + 1);
			if (!ptr[j])
				return (free_ptr(ptr, j));
			i += size;
			j++;
		}
	}
	ptr = pass_values(ptr, s, c, n_str);
	return (ptr);
}

char		**ft_split(char const *s, char c)
{
	char	**ptr;
	int		n_str;

	if (!s)
		return (NULL);
	n_str = number_str((char *)s, c);
	ptr = (char **)malloc(sizeof(char *) * (n_str + 1));
	if (!ptr)
		return (NULL);
	ptr = set_ptr(ptr, (char *)s, c, n_str);
	return (ptr);
}
