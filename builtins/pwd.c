/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:01:41 by ralopez-          #+#    #+#             */
/*   Updated: 2023/05/20 16:19:59 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd(t_inf *info, t_command *cmd)
{
	int	code;
	int	fd_write;

	code = 0;
	fd_write = 1;
	if (cmd->output != -2)
		fd_write = cmd->output;
	if (cmd->args != NULL && cmd->args[0] != NULL)
	{
		if (cmd->args != NULL && cmd->args[0] != NULL && cmd->args[0][0] == '-')
		{
			ft_putstr_fd("pwd: bad option: -", 2);
			ft_putchar_fd(cmd->args[0][1], 2);
			ft_putchar_fd('\n', 2);
		}
		else
			ft_putendl_fd("pwd: too many arguments", 2);
		code = 1;
		info->last_code = code;
	}
	else
	{
		code = get_pwd(info);
		info->last_code = code;
		ft_putendl_fd(info->pwd, fd_write);
	}
	return (code);
}
