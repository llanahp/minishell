/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:01:41 by ralopez-          #+#    #+#             */
/*   Updated: 2023/06/03 12:26:21 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	show_pwd(t_inf *info, int fd_write)
{
	int	code;

	code = get_pwd(info);
	info->last_code = code;
	ft_putendl_fd(info->pwd, fd_write);
	return (code);
}

int	pwd_args_correct(t_command *cmd)
{
	int	i;

	i = 1;
	while (cmd->args != NULL && cmd->args[0] != NULL && cmd->args[0][i])
	{
		if (cmd->args[0][i] != 'L' && cmd->args[0][i] != 'P')
			return (0);
		i++;
	}
	return (1);
}

char	pwd_invalid_char(t_command *cmd)
{
	int	i;

	i = 1;
	while (cmd->args != NULL && cmd->args[0] != NULL && cmd->args[0][i])
	{
		if (cmd->args[0][i] != 'L' && cmd->args[0][i] != 'P')
			return (cmd->args[0][i]);
		i++;
	}
	return (0);
}

int	pwd_display_error(t_command *cmd, t_inf *info)
{
	ft_putstr_fd("minishell: pwd: -", 2);
	ft_putchar_fd(pwd_invalid_char(cmd), 2);
	ft_putendl_fd(": invalid option", 2);
	ft_putstr_fd("pwd: usage: pwd [-LP]\n", 2);
	info->last_code = 1;
	return (1);
}

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
			if (pwd_args_correct(cmd) == 1)
				code = show_pwd(info, fd_write);
			else
				code = pwd_display_error(cmd, info);
		}
		else
			code = show_pwd(info, fd_write);
		info->last_code = code;
	}
	else
		code = show_pwd(info, fd_write);
	return (code);
}
