/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:41:20 by ralopez-          #+#    #+#             */
/*   Updated: 2023/05/20 18:56:19 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO revisar porque no se si es correcto
/*
int	io_sets(t_command *tmp)
{
	if ((tmp->input_name && tmp->input == -2) || (tmp->output_name && tmp->output == -2))
		return (1);
	else
		return (0);
}
*/

int	is_builtin(char *cmd)
{
	if (cmd == NULL)
		return (0);
	if (ft_strcmp(cmd, "echo") ==0|| ft_strcmp(cmd, "cd")  ==0|| ft_strcmp(cmd, "pwd")  ==0 || 
		ft_strcmp(cmd, "export")  ==0|| ft_strcmp(cmd, "unset")  ==0|| ft_strcmp(cmd, "env") ==0)
		return (1);
	return (0);
}


void	execute_builtin(t_command *cmd, t_inf *info)
{
	if (!ft_strcmp(cmd->cmd, "echo"))
		echo(cmd);
	else if (!ft_strcmp(cmd->cmd, "cd"))
		cd(info, cmd);
	else if (!ft_strcmp(cmd->cmd, "pwd"))
		pwd(info, cmd);
	else if (!ft_strcmp(cmd->cmd, "export"))
		export_binding(info, cmd);
	else if (!ft_strcmp(cmd->cmd, "unset"))
		unset(info, cmd);
	else if (!ft_strcmp(cmd->cmd, "env"))
		env(info);
	// exit() ?????
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
	
	redir(cmd);
	if (cmd != NULL && is_builtin(cmd->cmd))
		execute_builtin(cmd, info);
	else
	{
		cmd->cmd = get_path(cmd->cmd, info);
		if (execve(cmd->cmd, cmd->args, info->env) == -1)
		{
			if (cmd != NULL)
				// free(cmd);
			msg("Execve", ": ", strerror(errno), EXIT_FAILURE);
		}
	}
}

int	create_childs(t_inf *info)
{
	t_command	*tmp;

	tmp = info->commands;
	while (tmp)
	{
		tmp->pid = fork();
		if (tmp->pid == -1)
			msg("fork", "", strerror(errno), EXIT_FAILURE);
		else if (tmp->pid == 0)
			execute_cmd(tmp, info);
		tmp = tmp->next;
	}
	return (wait_childs(info));
	//return (0);
}




int	execute_commands(t_inf *info)
{
	int	code;

	code = prepare_execution(info);
	if (code != CMD_NOT_FOUND)
		return (code);
	
	code = create_childs(info);
	return (code);
}