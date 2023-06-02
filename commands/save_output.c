/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:08:25 by ralopez-          #+#    #+#             */
/*   Updated: 2023/03/31 14:08:27 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*save_output(t_inf *info, t_list *tmp, int type)
{
	t_command	*command;

	command = get_last_cmd(info);
	if (command->previous == NULL ||(command->previous->output != -2))
	{
		info->must_continue = 0;
		if (command->previous == NULL)
			ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
		else if (command->previous->output != -2 && type == O_TRUNC)
			ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
		else if (command->previous->output != -2 && type == O_APPEND)
			ft_putstr_fd("minishell: syntax error near unexpected token `>>'\n", 2);
		else
			ft_putstr_fd("minishell: syntax error \n", 2);
		info->last_code = 258;
		return (tmp->next);
	}
	tmp = tmp->next;
	if (command->output_name != NULL)
	{
		close(command->output);
		free(command->output_name);
		command->output_name = NULL;
	}
	if (tmp != NULL && tmp->type == WORD)
	{
		command->output_name = ft_strdup(tmp->content);
		command->output = open(command->output_name,  O_WRONLY | O_CREAT | type, 0664);
		if (command->output == -1)
		{
			msg(command->output_name,": No such file or directory","",1);
			info->last_code = 1;
			info->must_continue = 0;
		}
		tmp = tmp->next;
	}
	else
		command->output_name = NULL;
	return (tmp);
}
