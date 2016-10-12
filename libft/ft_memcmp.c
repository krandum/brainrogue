/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 12:54:42 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/21 12:54:43 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*us_s1;
	const unsigned char	*us_s2;

	us_s1 = (const unsigned char*)s1;
	us_s2 = (const unsigned char*)s2;
	i = 0;
	if (!s1 && !s2)
		return (0);
	if ((us_s1[0] == 0 || us_s2[0] == 0) && n == 0)
		return (0);
	while (i < n)
	{
		if (us_s1[i] != us_s2[i])
			return (us_s1[i] - us_s2[i]);
		i++;
	}
	if (i == n && i != 0)
		return (us_s1[i - 1] - us_s2[i - 1]);
	return (us_s1[i] - us_s2[i]);
}
