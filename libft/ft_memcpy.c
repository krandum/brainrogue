/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 12:13:32 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/21 12:13:34 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *source, size_t len)
{
	size_t		i;

	i = 0;
	while (i < len)
	{
		((char*)dest)[i] = ((char*)source)[i];
		i++;
	}
	return (dest);
}
