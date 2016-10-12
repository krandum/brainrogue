/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bsearch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 15:03:36 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/25 15:03:37 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**ft_bsearch(const void **tab, const void *target, size_t n,
	int (*cmpf)(const void *s1, const void *s2, size_t n))
{
	size_t	l;
	size_t	r;
	size_t	m;

	r = 0;
	while (tab[r])
		r++;
	l = 0;
	r--;
	while (l <= r)
	{
		m = (l + r) / 2;
		if (cmpf(tab[m], target, n) < 0)
			l = m + 1;
		else if (cmpf(tab[m], target, n) > 0)
			r = m - 1;
		else
			return ((void*)tab[m]);
	}
	return (NULL);
}
