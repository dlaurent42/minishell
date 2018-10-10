/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncasecmp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 22:37:12 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/10 22:37:50 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		 			ft_strncasecmp(const char *s1, const char *s2, size_t len)
{
	unsigned char	c1;
	unsigned char	c2;

	if (!s1 || !s2)
		return (1);
	if (!len)
		return (0);
	while (len--)
	{
		c1 = ft_tolower(*s1++);
		c2 = ft_tolower(*s2++);
		if (c1 != c2 || !c1)
			break ;
	}
	return ((int)c1 - (int)c2);
}
