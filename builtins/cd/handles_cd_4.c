/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handles_cd_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 18:20:12 by mpizzolo          #+#    #+#             */
/*   Updated: 2023/06/04 23:53:40 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// could use this to iterate over the cd 
// by splitting cmd->args
void	manage_cmd_args_cd(t_command *cmd)
{
	char	*str;
	int		args;

	str = cmd->args[0];
	args = 1;
}
