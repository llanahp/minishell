/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 13:07:01 by ralopez-          #+#    #+#             */
/*   Updated: 2023/06/03 13:07:03 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstclear_cmd_aux(t_command **aux, t_command **aux2)
{
	(*aux) = (*aux2);
	clear_command((*aux2));
	(*aux2) = (*aux2)->next;
	(*aux)->next = NULL;
	free((*aux));
	(*aux) = NULL;
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
				ft_lstclear_cmd_aux(&aux, &aux2);
			ft_lstclear_cmd_aux(&aux, &aux2);
		}
		info->commands = NULL;
	}
}

void	ft_clear_tokens_aux(t_list **aux, t_list **aux2)
{
	(*aux) = (*aux2);
	if ((*aux2)->content != NULL)
		free((*aux2)->content);
	(*aux2) = (*aux2)->next;
	(*aux)->next = NULL;
	free((*aux));
	(*aux) = NULL;
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
				ft_clear_tokens_aux(&aux, &aux2);
			ft_clear_tokens_aux(&aux, &aux2);
		}
		info->tokens = NULL;
	}
}
