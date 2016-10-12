/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 16:22:24 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/22 16:22:25 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strcpy_kinda(char *dest, const char *src, char delim)
{
	size_t	i;

	i = 0;
	while (src[i] != delim)
	{
		if (src[i] == '\0')
		{
			dest[i] = '\0';
			return (i + 1);
		}
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (i + 1);
}

static char	**split_function(char **current, const char *ori, int words, char d)
{
	int	i;
	int	temp;

	i = 0;
	temp = 0;
	while (i < words)
	{
		temp = ft_strcpy_kinda(current[i], ori, d);
		if (temp != 1)
			i++;
		while (temp-- > 0)
			ori++;
	}
	current[i] = NULL;
	return (current);
}

static int	attempt_alloc(char **array, int biggestword, int wordcount)
{
	int i;
	int i2;

	i = -1;
	while (++i < wordcount)
	{
		array[i] = (char*)malloc(sizeof(char) * (biggestword + 1));
		if (!array[i])
		{
			i2 = -1;
			while (++i2 < i)
				free(array[i2]);
			free(array);
			return (0);
		}
	}
	return (1);
}

static int	catch_nasties(char const *s, char c, char ***atab)
{
	if (!s)
	{
		*atab = NULL;
		return (1);
	}
	if (ft_strlen(s) == 0 && c)
	{
		*atab = (char**)malloc(sizeof(char*));
		**atab = NULL;
		return (1);
	}
	return (0);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**strarray;
	int		total;
	int		wordcount;
	int		biggestword;
	int		i;

	total = 0;
	wordcount = 0;
	biggestword = 0;
	i = 0;
	if (catch_nasties(s, c, &strarray))
		return (strarray);
	while (s[total])
		if (++i && s[++total] == c)
		{
			biggestword = i > biggestword ? i : biggestword;
			i = 0;
			wordcount += s[total - 1] == c ? 0 : 1;
		}
	wordcount += s[total - 1] == c ? 0 : 1;
	strarray = (char**)malloc(sizeof(char*) * (wordcount + 1));
	if (!strarray || !attempt_alloc(strarray, biggestword, wordcount))
		return (NULL);
	return (split_function(strarray, s, wordcount, c));
}
