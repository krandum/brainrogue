/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 12:47:07 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/21 12:47:09 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	void	*p;

	p = (void*)s;
	while (n-- > 0)
	{
		if (*(unsigned const char*)p == (unsigned const char)c)
			return (p);
		p++;
	}
	return (NULL);
}
