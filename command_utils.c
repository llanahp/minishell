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
}
