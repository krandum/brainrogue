/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 09:45:46 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/21 09:45:47 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(const char *big, const char *little)
{
	int		i;
	int		i2;
	int		found;
	char	*bb;

	bb = (char*)big;
	i = 0;
	if (little[0] == '\0')
		return (bb);
	while (bb[i] != '\0')
	{
		if (bb[i] == little[0])
		{
			found = i;
			i2 = 0;
			while (bb[i] == little[i2] && bb[i] != '\0')
				if (++i && little[++i2] == '\0')
					return (&(bb[found]));
			i = found + 1;
		}
		else
			i++;
	}
	return (0);
}
