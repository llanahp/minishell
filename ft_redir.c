/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:32:31 by ralopez-          #+#    #+#             */
/*   Updated: 2023/05/27 14:32:34 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** fds_pipes:
 * This function dups the input and output of two file descriptors.
 * 
 * If something went wrong, desalocate all memory and exit the program.
 */
void	fds_pipes(int in, int out)
{
	if (dup2(in, STDIN_FILENO) == -1)
	{
		exit(EXIT_FAILURE);
	}
	if (dup2(out, STDOUT_FILENO) == -1)
	{
		exit(EXIT_FAILURE);
	}
}

void	redir_files(t_command *cmd)
{
	if (cmd->input != -2 && cmd->output != -2)
	{
		fds_pipes(cmd->input, cmd->output);
		close(cmd->input);
		close(cmd->output);
	}
	else if (cmd->input != -2)
	{
		dup2(cmd->input, STDIN_FILENO);
		close(cmd->input);
	}
	else if (cmd->output != -2)
	{
		dup2(cmd->output, STDOUT_FILENO);
		close(cmd->output);
	}
}

void	close_pipe_fds(t_command *cmds, t_command *skip_cmd)
{
	while (cmds)
	{
		if (cmds != skip_cmd && cmds->fds)
		{
			close(cmds->fds[0]);
			close(cmds->fds[1]);
		}
		cmds = cmds->next;
	}
}

void	redir(t_command *cmd, t_inf *info)
{
	redir_files(cmd);
	if (cmd->previous != NULL && cmd->previous->pipe_out == 1)
		dup2(cmd->previous->fds[0], STDIN_FILENO);
	if (cmd->pipe_out)
		dup2(cmd->fds[1], STDOUT_FILENO);
	close_pipe_fds(info->commands, cmd);
}

void	close_files(t_command *cmd)
{
	if (cmd->input != -2)
	{
		close(cmd->input);
		cmd->input = -2;
	}
	if (cmd->output != -2)
	{
		close(cmd->output);
		cmd->output = -2;
	}
}
