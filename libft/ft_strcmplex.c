/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmplex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 10:34:05 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/26 10:34:06 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmplex(const char *s1, const char *s2)
{
	size_t				i;
	const unsigned char *ss1;
	const unsigned char *ss2;

	ss1 = (const unsigned char*)s1;
	ss2 = (const unsigned char*)s2;
	i = 0;
	while (ss1[i] && ss2[i])
	{
		if (ft_tolower((int)ss1[i]) != ft_tolower((int)ss2[i]))
			return (ft_tolower((int)ss1[i]) - ft_tolower((int)ss2[i]));
		else if (ss1[i] != ss2[i])
			return (ss1[i] - ss2[i]);
		i++;
	}
	return (ss1[i] - ss2[i]);
}
