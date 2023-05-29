/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:33:39 by ralopez-          #+#    #+#             */
/*   Updated: 2023/05/26 15:56:57 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_str_contains_n(char *str)
{
	int		res;
	int		i;

	res = 1;
	i = -1;
	while (str[++i] && res)
	{
		if (str[i] == '-' && str[i + 1] == 'n')
			res = 0;
	}
	return (res);
}

int	echo(t_command *cmd)
{
	int	i;
	int	is_n;

	i = 0;
	is_n = 0;
	if (!cmd->args[i])
		return (printf("\n"), 0);
	if (!ft_str_contains_n(cmd->args[i]))
	{
		is_n = 1;
		i++;
		while (cmd->args != NULL && !ft_str_contains_n(cmd->args[i]))
			i++;
	}
	while (cmd != NULL && cmd->args[i] != NULL && cmd->args && cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (!is_n)
		printf("\n");
	return (0);
}
