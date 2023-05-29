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

void	execute_builtin(t_command *cmd, t_inf *info, int exi)
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
	else if (!ft_strcmp(cmd->cmd, "env"))
		code = env(info);
	info->last_code = code;
	if (exi)
		exit(info->last_code);
}

/** create_cmd:
 * This function create the string with the command to execute
 * Desalocates the memory that dont use.
 */
char	*create_cmd(t_inf *info, int i, char *cmd)
{
	char	*cmd2;
	char	*res;

	cmd2 = ft_strjoin(info->paths[i], "/");
	res = ft_strjoin(cmd2, cmd);
	free(cmd2);
	return (res);
}

char	*get_path(char *cmd, t_inf *info)
{
	char	*cmd_ret;
	int		i;

	if (access(cmd, F_OK | X_OK) == 0)
	{
		return (cmd);
	}
	i = -1;
	while (info->paths[++i] != NULL)
	{
		cmd_ret = create_cmd(info, i, cmd);
		if (access(cmd_ret, F_OK | X_OK) == 0)
			break ;
		free(cmd_ret);
		cmd_ret = NULL;
	}
	free(cmd);
	return (cmd_ret);
}

void	execute_cmd(t_command *cmd, t_inf *info)
{
	char	*cmd_original;

	cmd_original = ft_strdup(cmd->cmd);
	redir(cmd, info);
	if (cmd != NULL && is_builtin(cmd->cmd))
		execute_builtin(cmd, info, 1);
	else
	{
		cmd->cmd = get_path(cmd->cmd, info);
		if (cmd->cmd == NULL)
		{
			msg("command not found", ": ", cmd_original, EXIT_FAILURE);
			info->last_code = 127;
			exit(info->last_code);
		}
		else if (execve(cmd->cmd, cmd->args, info->env) == -1)
		{
			msg("Execve", ": ", strerror(errno), EXIT_FAILURE);
			info->last_code = 127;
			exit(info->last_code);
		}
		info->last_code = 0;
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
			execute_cmd(tmp, info);
		tmp = tmp->next;
	}
	return (wait_childs(info));
}

int	execute_single_cmd(t_inf *info)
{
	t_command	*tmp;

	tmp = info->commands;
	execute_builtin(tmp, info, 0);
	info->last_code = 0;
	return (info->last_code);
}

int	num_cmds(t_inf *info)
{
	int			i;
	t_command	*aux;

	i = 0;
	aux = info->commands;
	while (aux)
	{
		i++;
		aux = aux->next;
	}
	return (i);
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
