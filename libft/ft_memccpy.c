/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 12:24:12 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/21 12:24:13 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t		i;
	char		*dd;
	const char	*ss;

	dd = (char*)dst;
	ss = (const char*)src;
	i = 0;
	while (i < n)
	{
		dd[i] = ss[i];
		if (ss[i++] == c)
			return ((void*)&(dd[i]));
	}
	return (0);
}
