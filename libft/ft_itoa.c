/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 17:58:27 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/22 17:58:28 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_digits(int n)
{
	int out;

	if (n == 0)
		return (1);
	out = 0;
	while (n)
	{
		out++;
		n /= 10;
	}
	return (out);
}

static char	*get_work(char *out, int n, size_t cmp, size_t len)
{
	out[len] = '\0';
	while (len-- > cmp)
	{
		out[len] = (n % 10) + '0';
		n /= 10;
		if (len == cmp && cmp == 1)
			out[0] = '-';
	}
	return (out);
}

char		*ft_itoa(int n)
{
	size_t	len;
	char	*out;
	size_t	cmp;

	cmp = 0;
	len = 0;
	if (n < 0)
	{
		len++;
		cmp = 1;
		if (n == -2147483648)
			return (ft_strdup("-2147483648"));
		n *= -1;
	}
	len += num_digits(n);
	out = (char*)malloc(sizeof(char) * (len + 1));
	if (!out)
		return (NULL);
	return (get_work(out, n, cmp, len));
}
