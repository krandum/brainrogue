/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/24 17:00:47 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/24 17:00:48 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlstnew(void const *content, size_t content_size)
{
	t_dlist	*out;

	out = (t_dlist*)malloc(sizeof(t_dlist));
	if (!out)
		return (NULL);
	if (!content)
	{
		out->content = NULL;
		out->content_size = 0;
	}
	else
	{
		out->content = malloc(content_size);
		if (!out->content)
			return (NULL);
		out->content = ft_memcpy(out->content, content, content_size);
		out->content_size = content_size;
	}
	out->next = NULL;
	out->prev = NULL;
	return (out);
}
