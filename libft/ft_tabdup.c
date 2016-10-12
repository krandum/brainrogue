/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 16:09:55 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/25 16:09:56 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	del_tab(char **tab)
{
	size_t i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	**ft_tabdup(const char **tab)
{
	char	**out;
	size_t	len;
	size_t	i;

	if (!tab)
		return (NULL);
	len = 0;
	while (tab[len])
		len++;
	out = (char**)malloc(sizeof(char*) * (len + 1));
	if (!out)
		return (NULL);
	i = -1;
	while (++i < len)
	{
		out[i] = ft_strdup(tab[i]);
		if (!out[i])
		{
			del_tab(out);
			return (NULL);
		}
	}
	out[i] = 0;
	return (out);
}
