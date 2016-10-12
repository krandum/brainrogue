/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <palatorr@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/09 11:58:18 by palatorr          #+#    #+#             */
/*   Updated: 2016/10/09 11:58:19 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	set_pack(t_pack **pack)
{
	*pack = (t_pack*)malloc(sizeof(t_pack));
	if (!*pack)
		return (1);
	(*pack)->len = BUFF_SIZE;
	(*pack)->str = (char*)malloc(((*pack)->len + 1) * sizeof(char));
	if (!(*pack)->str)
		return (1);
	(*pack)->str[(*pack)->len] = '\0';
	(*pack)->cur = 0;
	(*pack)->endl = (*pack)->str;
	(*pack)->has_read = 1;
	return (0);
}

/*
**	Necessary for small BUFF_SIZE values, make your line have more space
*/

static int	add_space(t_pack *pack)
{
	char	*new;
	long	size;

	size = pack->len * 2;
	if (size < pack->len + BUFF_SIZE)
		size += BUFF_SIZE;
	new = (char*)malloc((size + 1) * sizeof(char));
	if (!new)
		return (1);
	ft_strcpy(new, pack->str);
	new[size] = '\0';
	pack->endl = new + (pack->endl - pack->str);
	free(pack->str);
	pack->str = new;
	pack->len = size;
	return (0);
}

/*
**	Checks the difference in the addresses and compares with my cursor.
**	Sets my line's length like this.
*/

static int	set_endl(t_pack *pack)
{
	while (pack->cur > pack->endl - pack->str && *(pack->endl) != '\n')
		pack->endl++;
	if (*(pack->endl) == '\n')
		return (pack->cur > pack->endl - pack->str);
	return (0);
}

/*
**	In this assignment I learned to use the address to compare positions of 
**	characters in strings. Has what is essentially an ABORT condition which
**	will free everything.
*/

static int	shameless_split(t_pack **ppack, t_pack *pack, char **line)
{
	if (pack->has_read < 0)
		return (-1);
	*line = ft_strsub(pack->str, 0, pack->endl - pack->str);
	if (pack->has_read <= 0 || pack->cur <= 0)
	{
		if (pack->str)
			free(pack->str);
		free(pack);
		*ppack = NULL;
		return (0);
	}
	pack->cur += pack->str - pack->endl - (pack->has_read > 0 &&
		*(pack->endl) == '\n' && pack->cur != pack->endl - pack->str);
	ft_memcpy(pack->str, pack->endl + 1, pack->cur);
	pack->endl = pack->str;
	return (1);
}

/*
**	Sets my pack structure, checks for parameter errors
*/
int		ft_get_next_line(const int fd, char **line)
{
	static t_pack	*packs[MAX_PACKS];

	if (fd >= MAX_PACKS || fd < 0 || line == NULL)
		return (-1);
	if (packs[fd] && packs[fd]->has_read == 0)
		return (0);
	if (!packs[fd] && set_pack(&packs[fd]))
		return (-1);
	while (packs[fd]->has_read > 0 && !(set_endl(packs[fd])))
	{
		while (packs[fd]->cur + BUFF_SIZE > packs[fd]->len)
			if (add_space(packs[fd]))
				return (-1);
		packs[fd]->has_read = read(fd, packs[fd]->str + packs[fd]->cur,
			packs[fd]->len - packs[fd]->cur);
		packs[fd]->cur += packs[fd]->has_read;
	}
	return (shameless_split(&packs[fd], packs[fd], line));
}
