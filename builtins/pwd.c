/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:01:41 by ralopez-          #+#    #+#             */
/*   Updated: 2023/03/10 14:01:43 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int	pwd(t_inf *info, t_command *cmd)
{
	int	code;

	if (cmd->args != NULL)
	{
		if (cmd->args[0] != NULL && cmd->args[1][0] == '-')
			printf("pwd: bad option: -%c\n", cmd->args[1][1]);
		else
			printf("pwd: too many arguments\n");
		code = 1;
	}
	else
	{
		code = get_pwd(info);
		printf("%s\n",info->pwd);
	}
	return (code);
}

