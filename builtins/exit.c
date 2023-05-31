/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:41:20 by ralopez-          #+#    #+#             */
/*   Updated: 2023/05/29 20:01:56 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void    exiting(int numerror, t_inf *info)
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
			printf("exit\n");
			puterror(cmd->args[0], "numeric argument required");
			return (1);
		}
		i++;
	}
	return (0);
}

int	get_exit_error(t_command *cmd)
{
	int res;

	res = 0;
	cmd->args = cmd->args;
	// ft_atoi_exit
	return (res);
}

void	ft_exit(t_command *cmd, t_inf *info)
{
	int	numerror;

	
	if (!cmd->args[0])
		exit(0);
	if (cmd->args[1] != NULL)
	{
		ft_putstr_fd("exit\nbash: exit: too many arguments\n", 2);
		return ;
	}
	if (check_exit(cmd) == 1)
		exit(-1);
	numerror = get_exit_error(cmd);
	exiting(numerror, info);
}
