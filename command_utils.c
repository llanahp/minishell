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
	obj->previous = NULL;
	obj->input = -2;
	obj->output = -2;
	return (obj);
}

//TODO falta meter el previous
void	ft_lstadd_back_command(t_command **lst, t_command *new)
{
	t_command	*aux;

	if (lst != NULL)
	{
		aux = (*lst);
		if (aux != NULL)
		{
			while (aux != NULL && aux->next != NULL)
				aux = aux->next;
			aux->next = new;
		}
		else
			*lst = new;
	}
	else
	{
		lst = &new;
	}
}

void ft_free_array(char **array)
{
	int i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		array[i]= NULL;
		i++;
	}
	free(array);
	array = NULL;
}

void	clear_command(t_command *cmd)
{
	if (cmd->cmd != NULL)
		free(cmd->cmd);
	if (cmd->args != NULL)
		ft_free_array(cmd->args);
	
	if (cmd->path != NULL)
		free(cmd->path);
}

void	ft_lstclear_cmds(t_command *lst)
{
	t_command	*aux;
	t_command	*aux2;

	printf("DEBUG\n");
	getchar();
	
	if (lst != NULL)
	{
		aux = lst;
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
		lst = NULL;
	}
}