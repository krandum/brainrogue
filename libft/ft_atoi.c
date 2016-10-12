/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 10:47:36 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/21 10:47:38 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int					i;
	unsigned long long	ret;
	int					sign;

	i = 0;
	ret = 0;
	sign = 1;
	while (SPECIAL(str[i]))
		str++;
	if (str[i] == '-' || str[i] == '+')
	{
		sign = str[i] == '-' ? -1 : 1;
		str++;
	}
	while (*str == '0')
		str++;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (ret * sign);
		ret = ret * 10 + str[i++] - '0';
	}
	if (i > 19 || ret > 9223372036854775807ull)
		return (sign == 1 ? -1 : 0);
	return (sign * ret);
}
