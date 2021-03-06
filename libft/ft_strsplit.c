/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strsplit.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/09 14:21:43 by rkuijper       #+#    #+#                */
/*   Updated: 2019/08/02 09:47:27 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_split_count(const char *s, char c)
{
	int i;
	int j;
	int res;

	i = 0;
	j = 0;
	res = 0;
	while (s[i])
	{
		if (j == 1 && s[i] == c)
			j = 0;
		else if (j == 0 && s[i] != c)
		{
			j = 1;
			res++;
		}
		i++;
	}
	return (res);
}

static int	ft_word_length(const char *s, char c)
{
	int l;

	l = 0;
	while (*s && *s != c)
	{
		l++;
		s++;
	}
	return (l);
}

static char	**clean_memory(char **new)
{
	int i;

	if (new == NULL)
		return (NULL);
	i = 0;
	while (new[i] != NULL)
	{
		free(&(new[i]));
		i++;
	}
	free(new);
	return (NULL);
}

char		**ft_strsplit(const char *s, char c)
{
	int		j;
	int		len;
	char	**res;

	if (!s)
		return (NULL);
	j = 0;
	len = ft_split_count(s, c);
	res = (char**)ft_memalloc(sizeof(char*) * (len + 1));
	if (!res)
		return (NULL);
	while (len)
	{
		while (*s == c && *s)
			s++;
		res[j] = ft_strsub(s, 0, ft_word_length(s, c));
		if (res[j] == NULL)
			return (clean_memory(res));
		s += ft_word_length(s, c);
		j++;
		len--;
	}
	return (res);
}
