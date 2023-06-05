/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 09:39:01 by ralopez-          #+#    #+#             */
/*   Updated: 2023/06/03 23:29:40 by mpizzolo         ###   ########.fr       */
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
			return (p);
		}
		i++;
	}
	if (i < len && s[i] == c)
		p = ft_strdup((char *)s + i);
	return (p);
}
