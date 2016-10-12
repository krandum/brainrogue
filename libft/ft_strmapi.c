/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 14:39:50 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/22 14:39:51 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	size_t			len;
	char			*out;

	i = -1;
	if (!s || !*f)
		return (NULL);
	len = ft_strlen(s);
	out = (char*)malloc(sizeof(char) * (len + 1));
	if (!out)
		return (NULL);
	while (++i < (unsigned int)len)
		out[i] = f(i, s[i]);
	out[i] = '\0';
	return (out);
}
