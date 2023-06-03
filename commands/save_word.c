/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:08:25 by ralopez-          #+#    #+#             */
/*   Updated: 2023/03/31 14:08:27 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*save_word(t_inf *info, t_list *tmp)
{
	t_command	*command;

	command = get_last_cmd(info);
	if (command->cmd == NULL)
	{
		command->cmd = ft_strdup(tmp->content);
		tmp = tmp->next;
		tmp = save_args(tmp, command);
	}
	else
		tmp = save_args(tmp, command);
	return (tmp);
}
