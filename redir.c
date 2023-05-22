/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:41:20 by ralopez-          #+#    #+#             */
/*   Updated: 2023/03/10 10:41:21 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/** fds_pipes:
 * This function dups the input and output of two file descriptors.
 * 
 * If something went wrong, desalocate all memory and exit the program.
 */
void	fds_pipes(int in, int out)
{
	if (dup2(in, STDIN_FILENO) == -1)
	{
		//wfree_memory(info);
		exit(EXIT_FAILURE);
	}
	if (dup2(out, STDOUT_FILENO) == -1)
	{
		//free_memory(info);
		exit(EXIT_FAILURE);
	}
}

/*
int	*locate_redir(t_command *cmd)
{
	t_command *tmp = cmd;
	while (tmp != NULL && tmp->redir == NULL)
	{
		tmp = tmp->previous;
	}
	if (tmp == NULL)
		return (NULL);
	return (tmp->redir);
}*/

/** close_pipes:
 * This function close the previous file descriptors to the actual command.
 */
/*
void	close_pipes(int *redir, t_command *cmd)
{
	int	i;
	t_command *tmp = cmd;

	i = -1;
	if (cmd->input != -2)
	{
		close(cmd->input);
		cmd->input = -2;
	}
	if (cmd->output != -2)
	{
		close(cmd->output);
		cmd->input = -2;
	}

	while (tmp != NULL && (tmp->next != NULL && tmp->next->num_cmd_pipe > cmd->num_cmd_pipe))
	{
		tmp = tmp->next;
	}
	while (++i < (2 * (tmp->num_cmd_pipe)))
		close(redir[i]);
}*/

void	redir_files(t_command *cmd)
{
	if (cmd->input != -2 &&  cmd->output != -2)
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
	close_pipe_fds(info->commands ,cmd);
}
