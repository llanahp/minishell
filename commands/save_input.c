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

void	close_prev_redir(t_command *command)
{
	if (command->input_name != NULL)
	{
		close(command->input);
		free(command->input_name);
		command->input_name = NULL;
	}
}

t_list	*save_input(t_inf *info, t_list *tmp)
{
	t_command	*command;

	command = get_last_cmd(info);
	if (ft_error_syntax (tmp, info) == 1)
		return (NULL);
	tmp = tmp->next;
	close_prev_redir(command);
	if (tmp != NULL && tmp->type == WORD)
	{
		command->input_name = ft_strdup(tmp->content);
		command->input = open(command->input_name, O_RDONLY);
		if (command->input == -1)
		{
			msg(command->input_name, ": No such file or directory", "", 1);
			info->last_code = 1;
			info->must_continue = 0;
		}
		tmp = tmp->next;
	}
	else
		command->input_name = NULL;
	return (tmp);
}
