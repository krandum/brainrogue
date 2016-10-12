/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 14:31:25 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/22 14:31:26 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	i;
	size_t	len;
	char	*out;

	i = -1;
	if (!s || !*f)
		return (NULL);
	len = ft_strlen(s);
	out = (char*)malloc(sizeof(char) * (len + 1));
	if (!out)
		return (NULL);
	while (++i < len)
		out[i] = f(s[i]);
	out[i] = '\0';
	return (out);
}
