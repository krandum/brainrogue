/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 13:00:05 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/25 13:00:06 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		swap(void **s1, void **s2)
{
	void *t;

	t = *s1;
	*s1 = *s2;
	*s2 = t;
}

static t_range	get_range(size_t s, size_t e)
{
	t_range	out;

	out.start = s;
	out.end = e;
	return (out);
}

static void		quick(void **array, size_t n, t_range range,
	int (*cmpf)(const void *s1, const void *s2, size_t n))
{
	void	*pivot;
	size_t	left;
	size_t	right;

	if (range.start < range.end)
	{
		left = range.start + 1;
		right = range.end;
		pivot = array[range.start];
		while (left < right)
		{
			if (cmpf(array[left], pivot, n) <= 0)
				left++;
			else if (cmpf(array[right], pivot, n) >= 0)
				right--;
			else
				swap(&array[left], &array[right]);
		}
		if (cmpf(array[left], pivot, n) < 0)
			swap(&array[left--], &array[range.start]);
		else
			swap(&array[--left], &array[range.start]);
		quick(array, n, get_range(range.start, left), cmpf);
		quick(array, n, get_range(right, range.end), cmpf);
	}
}

void			ft_memsort(void **array, size_t n,
	int (*cmpf)(const void *s1, const void *s2, size_t n))
{
	size_t	len;

	len = 0;
	while (array[len])
		len++;
	quick(array, n, get_range(0, len - 1), cmpf);
}
