/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 14:09:16 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/22 14:09:18 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*out;

	out = (char*)malloc(sizeof(char) * (size + 1));
	if (!out)
		return (NULL);
	while (size)
		out[size--] = '\0';
	out[0] = '\0';
	return (out);
}
