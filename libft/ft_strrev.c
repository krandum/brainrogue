/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/24 21:39:50 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/24 21:39:54 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrev(char *str)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(str);
	i = -1;
	while (++i < len / 2)
	{
		str[i] ^= str[len - 1];
		str[len - 1] ^= str[i];
		str[i] ^= str[len - 1];
	}
	return (str);
}
