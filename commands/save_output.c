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

void	close_pre_output(t_command *command)
{
	if (command->output_name != NULL)
	{
		close(command->output);
		free(command->output_name);
		command->output_name = NULL;
	}
}

t_list	*save_output(t_inf *info, t_list *tmp, int type)
{
	t_command	*command;

	command = get_last_cmd(info);
	if (ft_error_syntax (tmp, info) == 1)
		return (NULL);
	tmp = tmp->next;
	close_pre_output(command);
	if (tmp != NULL && tmp->type == WORD)
	{
		command->output_name = ft_strdup(tmp->content);
		command->output = open(command->output_name,
				O_WRONLY | O_CREAT | type, 0664);
		if (command->output == -1)
		{
			info->last_code = msg(command->output_name, NOFILE, "", 1);
			info->must_continue = 0;
		}
		tmp = tmp->next;
	}
	else
		command->output_name = NULL;
	return (tmp);
}
