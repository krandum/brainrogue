/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 12:39:32 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/21 12:39:34 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		*dd;
	const char	*ss;

	dd = (char*)dst;
	ss = (const char*)src;
	if (dst > src)
		while (len--)
			dd[len] = ss[len];
	else
	{
		i = -1;
		while (++i < len)
			dd[i] = ss[i];
	}
	return (dst);
}
