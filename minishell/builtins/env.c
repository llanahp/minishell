/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:43:46 by ralopez-          #+#    #+#             */
/*   Updated: 2023/05/20 18:56:01 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env(t_inf *info)
{
	int	i;

	i = -1;
	if (info->env == NULL)
		return (1);
	while (info->env[++i])
		printf("%s\n", info->env[i]);
	return (0);
}
