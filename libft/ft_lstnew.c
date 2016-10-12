/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 19:32:08 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/22 19:32:09 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*out;

	out = (t_list*)malloc(sizeof(t_list));
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
	return (out);
}
