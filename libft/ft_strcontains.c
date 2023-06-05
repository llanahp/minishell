/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcontains.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:25:04 by ralopez-          #+#    #+#             */
/*   Updated: 2023/03/31 14:25:05 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcontains(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (c == '\0')
		return (0);
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return (1);
	return (0);
}

int	ft_strcontains_str(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str || !to_find)
		return (0);
	if (to_find[0] == '\0')
		return (0);
	while (str[i])
	{
		while (str[i + j] == to_find[j] && str[i + j] && to_find[j])
			j++;
		if (to_find[j] == '\0')
			return (1);
		j = 0;
		i++;
	}
	return (0);
}
