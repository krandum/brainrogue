/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 09:42:04 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/21 09:42:11 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;
	int		shhonlynullsnow;

	i = 0;
	shhonlynullsnow = 0;
	while (i < n)
	{
		if (src[i] != '\0')
			dest[i] = src[i];
		else
		{
			dest[i] = '\0';
			shhonlynullsnow = 1;
		}
		if (shhonlynullsnow)
			dest[i] = '\0';
		i++;
	}
	return (dest);
}
