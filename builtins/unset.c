/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:41:20 by ralopez-          #+#    #+#             */
/*   Updated: 2023/03/10 10:41:21 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int	unset(t_inf *info, t_command *cmd)
{
	char	**args;
	int     i;
	int		code;

	i = 1;
	code  = 0;
	while (cmd != NULL && cmd->args[i])
	{
		if (delete_var(info, cmd->args[i]) == 1 && code == 0)
			code = 1;
		i++;
	}
	return (code);
}