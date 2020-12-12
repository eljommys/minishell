/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_case.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 17:13:12 by marvin            #+#    #+#             */
/*   Updated: 2020/12/12 14:19:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int number_str(char *s, char c)
{
	int		i;
	int 	n;
	char 	quote;

	i = 0;
	n = 1;
	while (s[i])
	{
		if (s[i] == '\\' && (s[i + 1] == '\'' || s[i + 1] == '"' ||
							 s[i + 1] == '\\' || s[i + 1] == c))
			i++;
		else if (s[i] == c)
				n++;
		else if (s[i] && (s[i] == '"' || s[i] == '\''))
		{
			quote = s[i];
			i++;
			while (s[i] && s[i] != quote)
			{
				if (s[i] == '\\' && (s[i + 1] == quote || s[i + 1] == '\\') && quote == '"')
					i++;
				i++;
			}
		}
		i++;
	}
	return (n);
}

static int set_str_len(char *s, char c)
{
	char	quote;
	int		len;

	len = 0;
	while (s[len] && s[len] != c)
	{
		if (s[len] == '\\' && (s[len + 1] == '\'' ||
							   s[len + 1] == '"' || s[len + 1] == '\\' || s[len + 1] == c))
			len++;
		else if (s[len] == '"' || s[len] == '\'')
		{
			quote = s[len];
			len++;
			while (s[len] && s[len] != quote)
			{
				if (s[len] == '\\' && (s[len + 1] == quote || s[len + 1] == '\\') && quote == '"')
					len++;
				len++;
			}
		}
		len++;
	}
	return (len);
}

static void set_mat(char **mat, char *s, char c, int n)
{
	int i;
	int len;

	i = 0;
	while (i < n)
	{
		len = set_str_len(s, c);
		mat[i] = ft_strldup(s, len);
		s += len + 1;
		i++;
	}
}

char **ft_split_case(char *s, char c)
{
	int		n;
	char	**mat;

	if (!s)
		return (NULL);
	n = number_str(s, c);
	if (!(mat = (char **)ft_calloc(sizeof(char *), n + 1)))
		return (NULL);
	set_mat(mat, s, c, n);
	return (mat);
}
