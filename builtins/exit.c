/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:41:20 by ralopez-          #+#    #+#             */
/*   Updated: 2023/06/03 19:12:03 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exiting(int numerror, t_inf *info)
{
	free_memory(info);
	exit(numerror);
}

int	check_exit(t_command *cmd)
{
	int	i;

	i = 0;
	if (cmd->args[0][i] == '-' || cmd->args[0][i] == '+')
		i++;
	while (cmd->args[0][i])
	{
		if (!ft_isdigit(cmd->args[0][i]) + 0)
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cmd->args[0], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int	get_exit_error(t_command *cmd)
{
	int	res;

	res = ft_atoi_exit(cmd->args[0]);
	return (res);
}

int	ft_exit(t_command *cmd, t_inf *info)
{
	int	numerror;
	int	len;

	if (!cmd->args[0])
		exit(info->last_code);
	len = ft_strlen(cmd->args[0]);
	if (cmd->args[1] != NULL)
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
		return (1);
	}
	if (ft_isdigit(cmd->args[0][0]) == 0
		&& !(cmd->args[0][0] == '-' || cmd->args[0][0] == '+'))
	{
		ft_putstr_fd("exit\nminishell: exit: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exiting(255, info);
	}
	if (check_exit(cmd) == 1)
		exit(-1);
	numerror = get_exit_error(cmd);
	exiting(numerror, info);
	return (numerror);
}
