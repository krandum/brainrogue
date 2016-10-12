/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 14:19:35 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/22 14:19:37 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striter(char *s, void (*f)(char *))
{
	unsigned int	i;
	size_t			len;

	i = -1;
	if (!s || !*f)
		return ;
	len = ft_strlen(s);
	while (++i < (unsigned int)len)
		f(&(s[i]));
}
