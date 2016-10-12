/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palatorr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 09:50:50 by palatorr          #+#    #+#             */
/*   Updated: 2016/09/21 09:50:51 by palatorr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strcmp(const char *o_s1, const char *o_s2)
{
	int					i;
	const unsigned char	*s1;
	const unsigned char	*s2;

	s1 = (const unsigned char*)o_s1;
	s2 = (const unsigned char*)o_s2;
	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}
