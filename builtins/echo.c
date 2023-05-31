/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:33:39 by ralopez-          #+#    #+#             */
/*   Updated: 2023/05/26 15:56:57 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_str_contains_n(char *str)
{
	int		res;
	int		i;

	res = 1;
	i = -1;
	while (str[++i] && res)
	{
		if (str[i] == '-' && str[i + 1] == 'n')
			res = 0;
	}
	return (res);
}

int	echo(t_command *cmd)
{
	int	i;
	int	is_n;
	int	fd_write;

	i = 0;
	is_n = 0;
	fd_write = 1;
	if (cmd->output != -2)
		fd_write = cmd->output;
	if (!cmd->args[i])
	{
		ft_putstr_fd("\n", fd_write);
		return (0);
	}
	if (!ft_str_contains_n(cmd->args[i]))
	{
		is_n = 1;
		i++;
		while (cmd->args != NULL && !ft_str_contains_n(cmd->args[i]))
			i++;
	}
	while (cmd != NULL && cmd->args[i] != NULL && cmd->args && cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], fd_write);
		if (cmd->args[i + 1])
			ft_putstr_fd(" ", fd_write);
		i++;
	}
	if (!is_n)
		ft_putstr_fd("\n", fd_write);
	return (0);
}
