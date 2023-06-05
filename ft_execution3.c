/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:41:56 by ralopez-          #+#    #+#             */
/*   Updated: 2023/06/05 11:41:56 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all_pipes(t_command **command, t_command *actual)
{
	t_command	*tmp;

	tmp = *command;
	while (tmp != 0)
	{
		if (tmp != actual)
		{
			if (tmp->input != -2)
				close(tmp->input);
			if (tmp->output != -2)
				close(tmp->output);
		}
		tmp = tmp->next;
	}
}
