/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:41:20 by ralopez-          #+#    #+#             */
/*   Updated: 2023/05/25 09:47:10 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_command *cmd, t_inf *info, int exi)
{
	int	code;

	code = 127;
	if (!ft_strcmp(cmd->cmd, "echo"))
		code = echo(cmd);
	else if (!ft_strcmp(cmd->cmd, "cd"))
		code = cd(info, cmd);
	else if (!ft_strcmp(cmd->cmd, "pwd"))
		code = pwd(info, cmd);
	else if (!ft_strcmp(cmd->cmd, "export"))
		code = export_binding(info, cmd);
	else if (!ft_strcmp(cmd->cmd, "unset"))
		code = unset(info, cmd);
	else if (!ft_strcmp(cmd->cmd, "env")
		|| !ft_strcmp(cmd->cmd, "/usr/bin/env"))
		code = env(info);
	else if (!ft_strcmp(cmd->cmd, "exit"))
		code = ft_exit(cmd, info);
	info->last_code = code;
	if (exi)
		exit(info->last_code);
	return (code);
}

void	execute_cmd(t_command *cmd)
{
	char	*cmd_original;

	cmd_original = ft_strdup(cmd->cmd);
	redir(cmd, &g_info);
	if (cmd != NULL && is_builtin(cmd->cmd))
		execute_builtin(cmd, &g_info, 1);
	else
	{
		cmd->cmd = get_path(cmd->cmd, &g_info);
		if (cmd->cmd == NULL)
		{
			g_info.last_code = display_error_path(cmd_original);
			exit(g_info.last_code);
		}
		else if (execve(cmd->cmd, cmd->args, g_info.env) == -1)
		{
			g_info.last_code = msg("Execve", ": ", strerror(errno), errno);
			exit(g_info.last_code);
		}
		g_info.last_code = 0;
		if (cmd->cmd != NULL)
			free(cmd->cmd);
	}
}

int	create_childs(t_inf *info)
{
	t_command	*tmp;

	tmp = info->commands;
	while (tmp)
	{
		info->pid = fork();
		if (info->pid == -1)
			info->last_code = msg("fork", ": ", strerror(errno), EXIT_FAILURE);
		else if (info->pid == 0)
			execute_cmd(tmp);
			tmp = tmp->next;
	}
	return (wait_childs(info));
}

int	execute_single_cmd(t_inf *info)
{
	t_command	*tmp;

	tmp = info->commands;
	execute_builtin(tmp, info, 0);
	return (info->last_code);
}

int	execute_commands(t_inf *info)
{
	int	code;

	code = prepare_execution(info);
	if (code != CMD_NOT_FOUND)
		return (code);
	if (num_cmds(info) == 1 && is_builtin(info->commands->cmd))
		code = execute_single_cmd(info);
	else
		code = create_childs(info);
	return (code);
}
