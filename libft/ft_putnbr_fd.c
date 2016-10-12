/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 11:41:47 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/21 11:41:49 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int truncate;
	int called;

	called = 0;
	truncate = 1000000000;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		if (n == -2147483648)
		{
			ft_putchar_fd('2', fd);
			n %= 1000000000;
		}
		n *= -1;
	}
	while (truncate > 0)
	{
		if ((n / truncate) != 0 || called == 1 || (n == 0 && truncate == 1))
		{
			called = 1;
			ft_putchar_fd((n / truncate) + '0', fd);
		}
		n %= truncate;
		truncate /= 10;
	}
}
