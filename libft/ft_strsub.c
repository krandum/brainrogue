/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 15:24:36 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/22 15:24:37 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*out;
	size_t	i;

	i = -1;
	if (!s)
		return (NULL);
	out = (char*)malloc(sizeof(char) * (len + 1));
	if (!out)
		return (NULL);
	while (++i < len)
		out[i] = ((char*)s)[i + (size_t)start];
	out[i] = '\0';
	return (out);
}
