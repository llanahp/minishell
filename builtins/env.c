/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:43:46 by ralopez-          #+#    #+#             */
/*   Updated: 2023/06/03 16:05:38 by mpizzolo         ###   ########.fr       */
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
	if (ft_strcmp(info->commands->cmd, "env") == 0 && info->env[0] == NULL)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(&info->commands->cmd[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (127);
	}
	if (info->commands->output != -2)
		fd_write = info->commands->output;
	if (info->env == NULL)
		return (1);
	while (info->env[++i])
		ft_putendl_fd(info->env[i], fd_write);
	return (0);
}
