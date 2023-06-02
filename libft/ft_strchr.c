/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <ralopez-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 09:39:01 by ralopez-          #+#    #+#             */
/*   Updated: 2022/09/17 09:39:03 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*p;
	int		i;
	int		len;

	p = NULL;
	i = 0;
	len = ft_strlen(s);
	while (c > 127)
		c = c - 128;
	while (s != NULL && s[i])
	{
		if (s[i] == c)
		{
			p = ft_strdup((char *)s + i);
			break ;
		}
		i++;
	}
	if (i < len && s[i] == c)
		p = ft_strdup((char *)s + i);
	return (p);
}
