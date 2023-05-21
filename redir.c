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

void	redir(t_command *cmd)
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
	if (cmd->pipe_out == 1)
	{
		printf("(4)\n");
		close(cmd->fds[0]);
		dup2(cmd->fds[1], STDOUT_FILENO);

		close(cmd->fds[0]);
		close(cmd->fds[1]);

		/*if (cmd->input != -2)
			close(cmd->input);
		if (cmd->output!= -2)
			close(cmd->output);*/
	}
	
	
	if (cmd->previous != NULL && cmd->previous->pipe_out == 1)
	{
		close(cmd->fds[1]);
		dup2(cmd->fds[0], STDIN_FILENO);
	}
}
