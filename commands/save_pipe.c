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

t_list	*save_pipe(t_inf *info, t_list *tmp, int pipe)
{
	t_command	*command;

	command = get_last_cmd(info);
	if ((command->previous == NULL && command->next == NULL
			&& command->cmd == NULL)
		|| (command->previous != NULL && command->pipe_out == 1
			&& command->cmd == NULL && command->next == NULL
			&& command->cmd == NULL))
	{
		info->must_continue = 0;
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		info->last_code = 258;
		return (tmp->next);
	}
	if (ft_error_syntax (tmp, info) == 1)
		return (NULL);
	if (pipe)
		command->pipe_out = 1;
	ft_lstadd_back_command(&info->commands, ft_lstnew_command(NULL));
	return (tmp->next);
}
