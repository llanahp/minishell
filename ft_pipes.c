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

#include "minishell.h"

int	prepare_execution(t_inf *info)
{
	if (info == NULL || info->commands == NULL)
		return (CMD_SUCCESS);
	if (info->commands->cmd == NULL)
	{
		if (info->commands->input_name != NULL
			|| info->commands->output_name != NULL)
			return (CMD_FAILURE);
		return (CMD_SUCCESS);
	}
	if (prepare_pipes(info) == CMD_FAILURE)
		return (CMD_FAILURE);
	return (CMD_NOT_FOUND);
}

int	prepare_pipes(t_inf *info)
{
	t_command	*tmp;

	tmp = info->commands;
	while (tmp != NULL)
	{
		tmp->fds = malloc(sizeof(int *) * 2);
		if (tmp->fds == NULL || pipe(tmp->fds) != 0)
		{
			msg("malloc", ": ", strerror(errno), EXIT_FAILURE);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

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
	while ((wpid != -1 || errno != ECHILD))
	{
		wpid = waitpid(info->pid, &status, 0);
		if (wpid == info->pid)
			save_status = status;
		continue ;
	}
	if (WIFSIGNALED(save_status))
		status = 128 + WTERMSIG(save_status);
	else if (WIFEXITED(save_status))
		status = WEXITSTATUS(save_status);
	else
		status = save_status;
	return (status);
}
