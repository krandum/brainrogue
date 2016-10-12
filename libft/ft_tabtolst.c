/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrtolst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/24 15:34:19 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/24 15:34:20 by palatorr         ###   ########.fr       */
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

t_list		*ft_tabtolst(char **tab, int freetab)
{
	t_list	*head;
	t_list	*prev;
	t_list	*cur;
	size_t	i;

	i = 0;
	prev = NULL;
	while (tab[i])
	{
		cur = ft_lstnew(tab[i], sizeof(char*));
		if (!prev)
			head = cur;
		else
			prev->next = cur;
		if (!cur)
		{
			del_lst(head);
			return (NULL);
		}
		prev = cur;
		i++;
	}
	if (freetab)
		del_tab(tab);
	return (head);
}
