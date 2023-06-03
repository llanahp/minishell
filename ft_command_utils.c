/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <ralopez-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:51:43 by ralopez-          #+#    #+#             */
/*   Updated: 2022/09/13 15:53:03 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*ft_lstnew_command(char *cmd)
{
	t_command	*obj;

	obj = (t_command *) malloc(sizeof(*obj));
	if (!obj)
		return (0);
	obj->cmd = cmd;
	obj->args = NULL;
	obj->path = NULL;
	obj->fds = NULL;
	obj->next = NULL;
	obj->redir = NULL;
	obj->previous = NULL;
	obj->input_name = NULL;
	obj->output_name = NULL;
	obj->input = -2;
	obj->output = -2;
	obj->pipe_out = 0;
	obj->type_redir = 0;
	obj->num_cmd_pipe = 0;
	return (obj);
}

void	ft_lstadd_back_command(t_command **lst, t_command *new)
{
	t_command	*aux;

	new->next = NULL;
	if (lst != NULL)
	{
		aux = (*lst);
		if (aux != NULL)
		{
			while (aux != NULL && aux->next != NULL)
				aux = aux->next;
			aux->next = new;
			new->previous = aux;
		}
		else
			*lst = new;
	}
	else
		lst = &new;
}

void	clear_command2(t_command *cmd)
{
	int	i;

	i = 0;
	if (cmd->fds != NULL)
	{
		free(cmd->fds);
		cmd->fds = NULL;
	}
	if (cmd->redir != NULL)
	{
		while (cmd->redir[i])
		{
			close(cmd->redir[i]);
			i++;
		}
		free(cmd->redir);
	}
}

void	clear_command(t_command *cmd)
{
	if (cmd != NULL)
	{
		if (cmd->cmd != NULL)
			free(cmd->cmd);
		if (cmd->args != NULL)
			ft_free_split2(&cmd->args);
		if (cmd->path != NULL)
			free(cmd->path);
		if (cmd->input_name != NULL)
		{
			free(cmd->input_name);
			close(cmd->input);
		}
		if (cmd->output_name != NULL)
		{
			free(cmd->output_name);
			close(cmd->output);
		}
		clear_command2(cmd);
	}
}

t_command	*get_last_cmd(t_inf *info)
{
	t_command	*tmp;

	if (info->commands == NULL)
	{
		tmp = ft_lstnew_command(NULL);
		ft_lstadd_back_command(&info->commands, tmp);
		return (tmp);
	}
	tmp = info->commands;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	return (tmp);
}
