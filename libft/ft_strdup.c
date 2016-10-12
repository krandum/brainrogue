/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 13:06:31 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/21 13:06:32 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	len;
	char	*out;

	i = -1;
	len = ft_strlen(s1);
	out = (char*)malloc(sizeof(char) * (len + 1));
	if (!out)
		return (NULL);
	while (++i < len)
		out[i] = s1[i];
	out[i] = '\0';
	return (out);
}
