/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_case.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 17:13:12 by marvin            #+#    #+#             */
/*   Updated: 2020/12/13 14:55:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	number_str(char *s, char c)
{
	int		n[2];
	char	quote;

	n[0] = -1;
	n[1] = 1;
	while (s[++n[0]])
	{
		if (s[n[0]] == '\\' && (s[n[0] + 1] == '\'' || s[n[0] + 1] == '"' ||
								s[n[0] + 1] == '\\' || s[n[0] + 1] == c))
			n[0]++;
		else if (s[n[0]] == c)
			n[1]++;
		else if (s[n[0]] && (s[n[0]] == '"' || s[n[0]] == '\''))
		{
			quote = s[n[0]++];
			while (s[n[0]] && s[n[0]] != quote)
			{
				if (s[n[0]] == '\\' &&
				(s[n[0] + 1] == quote || s[n[0] + 1] == '\\') && quote == '"')
					n[0]++;
				n[0]++;
			}
		}
	}
	return (n[1]);
}

static int	set_str_len(char *s, char c)
{
	char	quote;
	int		len;

	len = -1;
	while (s[++len] && s[len] != c)
	{
		if (s[len] == '\\' && (s[len + 1] == '\'' || s[len + 1] == '"' ||
		s[len + 1] == '\\' || s[len + 1] == c))
			len++;
		else if (s[len] == '"' || s[len] == '\'')
		{
			quote = s[len++];
			while (s[len] && s[len] != quote)
			{
				if (s[len] == '\\' &&
				(s[len + 1] == quote || s[len + 1] == '\\') && quote == '"')
					len++;
				len++;
			}
		}
	}
	return (len);
}

static void	set_mat(char **mat, char *s, char c, int n)
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

char		**ft_split_case(char *s, char c)
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
