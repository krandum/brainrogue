/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 14:18:55 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/21 14:18:56 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	i2;
	size_t	destlen;
	size_t	spaceleft;

	i = 0;
	i2 = 0;
	destlen = 0;
	while (dest[i])
	{
		i++;
		destlen++;
		if (destlen >= size)
			return (size + ft_strlen(src));
	}
	spaceleft = size - destlen;
	while (src[i2] != '\0' && i < size)
	{
		if (--spaceleft > 0)
			dest[i] = src[i2];
		i++;
		i2++;
	}
	dest[i - (i == size ? 1 : 0)] = '\0';
	return (destlen + ft_strlen(src));
}
