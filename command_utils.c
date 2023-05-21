/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
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
/*
void ft_free_array(char ***array)
{
	int i;

	i = 0;
	while ((*array) != NULL && (*array)[i] != NULL)
	{
		free((*array)[i]);
		(*array)[i] = NULL;
		i++;
	}
	if ((*array) != NULL)
		free((*array));
	(*array) = NULL;
}*/

//TODO falta liberar el previous y next 
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
	}
}

void	ft_lstclear_cmds(t_inf *info)
{
	t_command	*aux;
	t_command	*aux2;
	
	if (info->commands != NULL)
	{
		
		aux = info->commands;
		if (aux != NULL)
		{
			aux2 = aux;
			while (aux2 != NULL && aux2->next != NULL)
			{
				aux = aux2;
				clear_command(aux2);
				aux2 = aux2->next;
				aux->next = NULL;
				free(aux);
				aux = NULL;
			}
			aux = aux2;
			clear_command(aux2);
			aux2 = aux2->next;
			aux->next = NULL;
			free(aux);
			aux = NULL;
		}
		info->commands = NULL;
	}
}

void	ft_clear_tokens(t_inf *info)
{
	t_list	*aux;
	t_list	*aux2;
	
	if (info->tokens != NULL)
	{	
		aux = info->tokens;
		if (aux != NULL)
		{
			aux2 = aux;
			while (aux2 != NULL && aux2->next != NULL)
			{
				aux = aux2;
				if (aux2->content != NULL)
					free(aux2->content);
				aux2 = aux2->next;
				aux->next = NULL;
				free(aux);
				aux = NULL;
			}
			aux = aux2;
			if (aux2->content != NULL)
				free(aux2->content);
			aux2 = aux2->next;
			aux->next = NULL;
			free(aux);
			aux = NULL;
		}
		info->tokens = NULL;
	}
}

t_command	*get_last_cmd(t_inf *info)
{
	t_command	*tmp;
	if (info->commands == NULL)
	{
		/*tmp = (t_command *)malloc(sizeof(t_command) * 1);
		if (!tmp)
			return (NULL);*/
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