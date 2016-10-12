/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 15:36:42 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/25 15:36:43 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	putelem(t_list *elem)
{
	ft_putstr((char*)elem->content);
}

void	ft_putlst(t_list *head, const char *d)
{
	t_list	*cur;

	cur = head;
	while (cur)
	{
		putelem(cur);
		if (cur->next)
			ft_putstr(d);
		cur = cur->next;
	}
	ft_nl();
}
