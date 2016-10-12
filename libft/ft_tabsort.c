/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 10:45:43 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/26 10:45:45 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		swap(char **s1, char **s2)
{
	char	*t;

	t = *s1;
	*s1 = *s2;
	*s2 = t;
}

static void		quick(char **table, size_t start, size_t end,
	int (*cmpf)(const char *s1, const char *s2))
{
	char	*pivot;
	size_t	left;
	size_t	right;

	if (start < end)
	{
		left = start + 1;
		right = end;
		pivot = table[start];
		while (left < right)
		{
			if (cmpf(table[left], pivot) <= 0)
				left++;
			else if (cmpf(table[right], pivot) >= 0)
				right--;
			else
				swap(&table[left], &table[right]);
		}
		if (cmpf(table[left], pivot) < 0)
			swap(&table[left--], &table[start]);
		else
			swap(&table[--left], &table[start]);
		quick(table, start, left, cmpf);
		quick(table, right, end, cmpf);
	}
}

void			ft_tabsort(char **table,
	int (*cmpf)(const char *s1, const char *s2))
{
	size_t	len;

	len = 0;
	while (table[len])
		len++;
	quick(table, 0, len - 1, cmpf);
}
