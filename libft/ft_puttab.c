/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puttab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 14:30:38 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/25 14:30:39 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_puttab(char const **tab, const char *d)
{
	size_t	i;

	i = -1;
	if (!tab)
		return ;
	while (tab[++i])
	{
		ft_putstr(tab[i]);
		if (tab[i + 1])
			ft_putstr(d);
	}
	ft_nl();
}
