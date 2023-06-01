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

int	env_export(t_inf *info)
{
	int	i;
	int	fd_write;

	i = -1;
	fd_write = 1;
	if (info->commands->output != -2)
		fd_write = info->commands->output;
	if (info->env == NULL)
		return (1);
	while (info->env[++i])
	{
		ft_putstr_fd("declare -x ", fd_write);
		ft_putendl_fd(info->env[i], fd_write);
	}
	return (0);
}

int	env(t_inf *info)
{
	int	i;
	int	fd_write;

	i = -1;
	fd_write = 1;
	if (info->commands->output != -2)
		fd_write = info->commands->output;
	if (info->env == NULL)
		return (1);
	while (info->env[++i])
		ft_putendl_fd(info->env[i], fd_write);
	return (0);
}
