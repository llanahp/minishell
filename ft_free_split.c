/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 10:52:07 by ralopez-          #+#    #+#             */
/*   Updated: 2023/06/01 14:44:14 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_split(char **split)
{
	int		i;

	i = 0;
	if (split != NULL)
	{
		while (split[i])
		{
			free(split[i]);
			i++;
		}
		free(split);
	}
}

void	ft_free_split2(char ***split)
{
	int		i;

	i = 0;
	if ((*split) != NULL)
	{
		while ((*split)[i])
		{
			free((*split)[i]);
			i++;
		}
		free((*split));
		(*split) = NULL;
	}
}
