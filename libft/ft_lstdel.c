/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 11:04:13 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/23 11:04:15 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*cur;
	t_list	*tmp;

	cur = *alst;
	while (cur)
	{
		del(cur->content, cur->content_size);
		tmp = cur;
		cur = cur->next;
		free(tmp);
	}
	*alst = NULL;
}
