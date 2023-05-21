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
}

/** close_pipes:
 * This function close the previous file descriptors to the actual command.
 */
void	close_pipes(int *redir,t_command *cmd)
{
	int	i;

	i = -1;
	while (++i < (2 * (cmd->num_cmd_pipe - 1)))
	{
		close(redir[i]);
	}
}

void	redir(t_command *cmd)
{
	int	*redir;

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
	printf("cmd:%s\n", cmd->cmd);
	printf("type_redir:%d\n", cmd->type_redir);
	printf("num_cmd_pipe:%d\n\n", cmd->num_cmd_pipe);
	if (cmd->type_redir != 0)
	{
		redir = locate_redir(cmd);
		if (cmd->type_redir == 1)
		{
			if (dup2(redir[1], STDOUT_FILENO) == -1)
				exit(EXIT_FAILURE);
		}
		else if (cmd->type_redir == 3)
		{
			if (dup2(redir[2 * cmd->num_cmd_pipe - 2], STDIN_FILENO) == -1)
				exit(EXIT_FAILURE);
		}
		else
			fds_pipes(redir[2 * cmd->num_cmd_pipe - 2], redir[2 * cmd->num_cmd_pipe + 1]);
		close_pipes(redir, cmd);
	}
	
	
}
