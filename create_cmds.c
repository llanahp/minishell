/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:41:40 by ralopez-          #+#    #+#             */
/*   Updated: 2023/03/31 10:41:42 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "minishell.h"

void mostrar_commands(t_inf *info)
{
	t_command	*tmp;

	tmp = info->commands;
	printf("--------------\n");
	while (tmp != NULL)
	{
		printf("cmd:%s\n", (char *)tmp->cmd);
		int i=0;
		while (tmp->args[i] != NULL)
		{
			printf("args(%d): %s\n",i, tmp->args[i]);
			i++;
		}
		tmp = tmp->next;
		
	}
}

int	create_commands(t_inf *info)
{
	if (info->tokens == NULL)
		return (0);
	t_list	*tmp;
	tmp = info->tokens;
	while (tmp)
	{
		if (tmp != NULL && tmp->type == WORD)
			tmp  = save_word(info, tmp);
		else if (tmp->type == LESS)
			tmp  = save_input(info, tmp);
		else if (tmp->type == GREATER)
			tmp  = save_output(info, tmp, O_TRUNC);
		else if (tmp->type == APPEND)
			tmp  = save_output(info, tmp, O_APPEND);
		else if (tmp->type == PIPE)// |
			tmp = save_pipe(info, tmp, 1);
		else if (tmp->type == SEMICOLON) // ;
			tmp = save_pipe(info, tmp, 0);
		else if (tmp->type == HEREDOC) //<<
			tmp = save_heredoc(info, tmp);
		else if (tmp != NULL && tmp->type == END)
		{
			break;
		}
		
		/*else
		{
			ft_lstadd_back(&info->commands, ft_lstnew(tmp->content));
			tmp = tmp->next;
		}*/
		
	}
	mostrar_commands(info);
	return (0);
}