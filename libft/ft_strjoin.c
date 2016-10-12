/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 15:59:59 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/22 16:00:07 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*out;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	out = (char*)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!out)
		return (NULL);
	out[len1 + len2] = '\0';
	while (len2--)
		out[len1 + len2] = ((char*)s2)[len2];
	while (len1--)
		out[len1] = ((char*)s1)[len1];
	return (out);
}
