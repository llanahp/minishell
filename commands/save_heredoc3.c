/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_heredoc3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 15:25:14 by ralopez-          #+#    #+#             */
/*   Updated: 2023/06/04 15:25:15 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_heredoc(t_command *command, t_inf *info, int *heredoc, char *deli)
{
	signal(SIGINT, handle_sigint_heredoc);
	close(heredoc[0]);
	read_heredoc(command->input_name, deli, info);
	close(heredoc[1]);
	exit(0);
}

void	wait_child_here(int *wpid, int pid, int *save_status)
{
	int	status;

	while (((*wpid) != -1 || errno != ECHILD))
	{
		(*wpid) = waitpid(pid, &status, 0);
		if ((*wpid) == pid)
			(*save_status) = status;
		continue ;
	}
}

int	parent_heredoc(t_command *command, int *heredoc, int pid)
{
	pid_t	wpid;
	int		save_status;

	wpid = 0;
	signal(SIGINT, SIG_IGN);
	wait_child_here(&wpid, pid, &save_status);
	close(heredoc[1]);
	if (WIFEXITED(save_status))
	{
		save_status = WEXITSTATUS(save_status);
		if (save_status == 1)
		{
			g_info.last_code = 1;
			g_info.must_continue = 0;
			return (-3);
		}
		else
			command->input = dup(heredoc[0]);
		close(heredoc[0]);
	}
	return (0);
}

int	heredoc_fork(t_inf *info, t_command *command, char *delimiter)
{
	int	pid;
	int	heredoc[2];
	int	i;

	i = pipe(heredoc);
	if (i == -1)
		exit(1);
	pid = fork();
	if (pid == 0)
		child_heredoc(command, info, heredoc, delimiter);
	else
		return (parent_heredoc(command, heredoc, pid));
	return (0);
}
