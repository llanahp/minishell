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

int	is_path_null(t_inf *info)
{
	int		i;
	char	*temp;

	i = 0;
	if (info->env == NULL)
		return (1);
	while (info->env[i] != NULL && info->env[i][0] != '\0'
		&& ft_strncmp(info->env[i], "PATH=", 5) != 0)
		i++;
	if (info->env != NULL && (info->env[i] == NULL || ft_strncmp(info->env[i], "PATH=", 5)) != 0)
		return (1);
	else
	{
		temp = ft_substr(info->env[i], 5, ft_strlen(info->env[i]));
		if (temp == NULL || temp[0] == '\0')
		{
			free(temp);
			return (1);
		}
		else
		{
			free(temp);
			return (0);
		}
	}
	return (1);
}



int	env(t_inf *info)
{
	int	i;
	int	fd_write;

	i = -1;
	fd_write = 1;
	//if (ft_strcmp(info->commands->cmd, "/usr/bin/env") == 0)
	if (ft_strcmp(info->commands->cmd, "env") == 0 && is_path_null(info) == 1)
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
