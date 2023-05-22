/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:41:20 by ralopez-          #+#    #+#             */
/*   Updated: 2023/05/20 18:55:44 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unset(t_inf *info, t_command *cmd)
{
	int		i;
	int		code;

	i = 0;
	code = 0;
	while (cmd != NULL && cmd->args[i])
	{
		if (delete_var(info, cmd->args[i]) == 1 && code == 0)
			code = 1;
		i++;
	}
	return (code);
}
