/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 15:56:04 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/21 15:56:05 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*out;
	char	*tmp;

	out = malloc(size);
	if (!out)
		return (NULL);
	tmp = (char*)out;
	while (size--)
		*tmp++ = '\0';
	return (out);
}
