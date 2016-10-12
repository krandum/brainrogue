/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 16:09:45 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/22 16:09:46 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	start;
	size_t	end;
	size_t	len;
	char	*out;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	i = 0;
	while (WHITE(s[i]))
		i++;
	start = i;
	i = len - 1;
	while (WHITE(s[i]))
		i--;
	end = i + 1;
	if (start == len)
		return (ft_strnew(0));
	out = ft_strsub(s, (unsigned int)start, end - start);
	return (out);
}
