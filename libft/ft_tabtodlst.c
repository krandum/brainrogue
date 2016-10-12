/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabtodlst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/24 17:05:33 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/24 17:05:34 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	del_dlst(t_dlist *lst)
{
	t_dlist	*temp;

	while (lst)
	{
		temp = lst;
		free(lst->content);
		lst = lst->next;
		free(temp);
	}
}

static void	del_tab(char **tab)
{
	size_t i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

t_dlist		*ft_tabtodlst(char **tab, int freetab)
{
	t_dlist	*head;
	t_dlist	*prev;
	t_dlist	*cur;
	size_t	i;

	i = 0;
	prev = NULL;
	while (tab[i])
	{
		cur = ft_dlstnew(tab[i], sizeof(char*));
		if (!prev)
			head = cur;
		else
			prev->next = cur;
		if (++i && !cur)
		{
			del_dlst(head);
			return (NULL);
		}
		cur->prev = prev;
		prev = cur;
	}
	if (freetab)
		del_tab(tab);
	return (head);
}
