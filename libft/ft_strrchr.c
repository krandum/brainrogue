/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 14:33:18 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/21 14:33:19 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*ss;

	ss = (char*)s;
	i = ft_strlen(s);
	if (!s[i] && !c)
		return (&(ss[i]));
	while (i && s[i - 1])
		if (s[--i] == c)
			return (&(ss[i]));
	return (0);
}
