/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:41:20 by ralopez-          #+#    #+#             */
/*   Updated: 2023/03/10 10:41:21 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	prepare_execution(t_inf *info)
{
	if (info == NULL || info->commands == NULL)
		return (CMD_SUCCESS);
	if (info->commands->cmd == NULL)
	{
		if (info->commands->input_name != NULL || info->commands->output_name != NULL)
			return (CMD_FAILURE);
		return (CMD_SUCCESS);
	}
	if (prepare_pipes(info) == CMD_FAILURE)
		return (CMD_FAILURE);
	return (CMD_NOT_FOUND);
}
/*
int	num_cmd_pipe(t_command *tmp)
{
	int	i;

	i = 0;
	tmp->type_redir = 1;//start pipe
	tmp->num_cmd_pipe = i;
	//printf("(1)\n");
	tmp = tmp->next;
	while (tmp != NULL && tmp->pipe_out)
	{
		i++;
		tmp->type_redir = 2;//middle pipe
		//printf("(2)\n");
		tmp->num_cmd_pipe = i;
		tmp = tmp->next;
	}
	if (tmp != NULL)
	{
		i++;
		tmp->type_redir = 3;//end pipe
	//	printf("(3)\n");
		tmp->num_cmd_pipe = i ;
	}
	//printf("->num_cmd_pipe = %d<-\n", i);
	return (i);
}

t_command	*reserve_space_redir(t_command *tmp)
{

	tmp->redir = malloc(sizeof(int *) * num_cmd_pipe(tmp) * 2);
	if (tmp->redir == NULL || pipe(tmp->redir) != 0)
	{
			//todo free memory de todo lo anterior
			//free_error("error malloc", "", "", info);
			return (NULL);
	}
	while (tmp != NULL && tmp->pipe_out)
		tmp = tmp->next;
	return (tmp);
}*/


int	prepare_pipes(t_inf *info)
{
	t_command	*tmp;

	tmp = info->commands;
	while (tmp != NULL)
	{
		tmp->fds = malloc(sizeof(int *) * 2);
		if (tmp->fds == NULL || pipe(tmp->fds) != 0)
		{
			//todo free memory de todo lo anterior
			//free_error("error malloc", "", "", info);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
/*
int	prepare_pipes(t_inf *info)
{
	t_command	*tmp;

	tmp = info->commands;
	while (tmp != NULL)
	{
		if (tmp->pipe_out)
			tmp = reserve_space_redir(tmp);
		else
			tmp = tmp->next;		
	}
	return (0);
}*/

void	close_pipes(t_inf *info)
{
	t_command	*tmp;

	tmp = info->commands;
	while (tmp != NULL)
	{
		close(tmp->fds[0]);
		close(tmp->fds[1]);
		if (tmp->input != -2)
			close(tmp->input);
		if (tmp->output != -2)
			close(tmp->output);
		tmp = tmp->next;

	}
}

int	wait_childs(t_inf *info)
{
	pid_t	wpid;
	int		status;
	int		save_status;

	close_pipes(info);
	save_status = 0;
	wpid = 0;
	while ((wpid != -1 || errno != ECHILD) )
	{
		wpid = waitpid(info->pid, &status, 0);
		if (wpid == info->pid)
			save_status = status;
		continue ;
	}
	return (save_status);
}