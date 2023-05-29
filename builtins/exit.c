/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:41:20 by ralopez-          #+#    #+#             */
/*   Updated: 2023/05/29 19:46:11 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exiting(int numerror)
{
	// frees
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

void	ft_exit(t_command *cmd)
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
		exit(255);
	numerror = ft_atoi_exit(cmd->args[0]);
	exiting(numerror);
}
