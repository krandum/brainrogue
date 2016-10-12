/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 11:42:36 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/23 11:42:37 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	del_lst(t_list *lst)
{
	t_list	*temp;

	while (lst)
	{
		temp = lst;
		free(lst->content);
		lst = lst->next;
		free(temp);
	}
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*cur;
	t_list	*prev;
	t_list	*head;

	prev = NULL;
	while (lst)
	{
		cur = f(lst);
		cur = ft_lstnew(cur->content, cur->content_size);
		if (!prev)
			head = cur;
		else
			prev->next = cur;
		if (!cur)
		{
			del_lst(head);
			return (NULL);
		}
		lst = lst->next;
		prev = cur;
	}
	return (head);
}
