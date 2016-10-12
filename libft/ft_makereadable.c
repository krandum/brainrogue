/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_makereadable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/24 15:51:18 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/24 15:51:20 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** This function will return a character for every byte in data, in base 64.
** Uppercase letters go first, then lowercase, numbers and finally + and /.
** The string returned will be a new string and as such will need to be freed.
*/

char	*ft_makereadable(const void *data, size_t len)
{
	size_t	i;
	char	*out;
	char	c;

	i = -1;
	out = ft_strdup((char*)data);
	if (!out)
		return (NULL);
	while (++i < len)
	{
		c = out[i];
		c %= 64;
		if (c >= 0 && c <= 25)
			c += 'a';
		else if (c >= 26 && c <= 51)
			c += 'A' - 26;
		else if (c >= 52 && c <= 61)
			c += '0' - 52;
		else if (c == 62)
			c = '+';
		else if (c == 63)
			c = '/';
		out[i] = c;
	}
	return (out);
}
