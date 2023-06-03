/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:41:40 by ralopez-          #+#    #+#             */
/*   Updated: 2023/06/01 14:50:07 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prepare_args(t_inf *info)
{
	t_command	*tmp;
	int			i;

	tmp = info->commands;
	i = 0;
	while (tmp)
	{
		if (tmp->cmd != NULL && !is_builtin(tmp->cmd))
			tmp->args = join_arguments(ft_split(tmp->cmd, ' '), tmp->args);
		tmp = tmp->next;
		i++;
	}
}

int	create_commands(t_inf *info)
{
	t_list	*tmp;

	if (info->tokens == NULL)
		return (0);
	tmp = info->tokens;
	while (tmp && info->must_continue)
	{
		if (tmp != NULL && tmp->type == WORD)
			tmp = save_word(info, tmp);
		else if (tmp->type == LESS)
			tmp = save_input(info, tmp);
		else if (tmp->type == GREATER)
			tmp = save_output(info, tmp, O_TRUNC);
		else if (tmp->type == APPEND)
			tmp = save_output(info, tmp, O_APPEND);
		else if (tmp->type == PIPE)
			tmp = save_pipe(info, tmp, 1);
		else if (tmp->type == HEREDOC)
			tmp = save_heredoc(info, tmp);
		else if (tmp != NULL && tmp->type == END)
			break ;
	}
	if (info->must_continue)
		prepare_args(info);
	return (0);
}
