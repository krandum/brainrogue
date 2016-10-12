/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 11:28:13 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/21 11:28:15 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	int truncate;
	int called;

	called = 0;
	truncate = 1000000000;
	if (n < 0)
	{
		ft_putchar('-');
		if (n == -2147483648)
		{
			ft_putchar('2');
			n %= 1000000000;
		}
		n *= -1;
	}
	while (truncate > 0)
	{
		if ((n / truncate) != 0 || called == 1 || (n == 0 && truncate == 1))
		{
			called = 1;
			ft_putchar((n / truncate) + '0');
		}
		n %= truncate;
		truncate /= 10;
	}
}
