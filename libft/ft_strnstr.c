/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 14:57:09 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/21 14:57:10 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	i2;
	size_t	found;
	char	*bb;

	bb = (char*)big;
	i = 0;
	if (little[0] == '\0')
		return (bb);
	while (big[i] != '\0' && i < len)
	{
		if (big[i] == little[0])
		{
			found = i;
			i2 = 0;
			while (big[i] == little[i2] && big[i] != '\0' && i < len)
				if (++i && little[++i2] == '\0')
					return (&(bb[found]));
			i = found + 1;
		}
		else
			i++;
	}
	return (0);
}
