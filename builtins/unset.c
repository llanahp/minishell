/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:41:20 by ralopez-          #+#    #+#             */
/*   Updated: 2023/06/03 17:04:50 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_invalid_argument(char *arg, int screen)
{
	if (((arg != NULL && arg[0] == '\0')
			|| ft_strcontains(arg, '=') || ft_strcontains(arg, '?')
			|| ft_strcontains(arg, '$') || ft_strcontains(arg, ';')
			|| ft_strcontains(arg, '.') || ft_strcontains(arg, '+')
			|| ft_strcontains(arg, '{') || ft_strcontains(arg, '}')
			|| ft_strcontains(arg, '-') || ft_strcontains(arg, '@')
			|| ft_strcontains(arg, '#') || ft_strcontains(arg, '*')
			|| ft_strcontains(arg, '^') || ft_strcontains(arg, '~')
			|| ft_strcontains(arg, '!')) && screen == 0)
	{
		return (1);
	}
	return (0);
}

int	unset(t_inf *info, t_command *cmd)
{
	int	i;
	int	code;
	int	screen;

	i = 0;
	code = 0;
	screen = 0;
	while (cmd != NULL && cmd->args[i])
	{
		if (is_invalid_argument(cmd->args[i], screen) == 1)
		{
			ft_putstr_fd("unset: ", 2);
			ft_putstr_fd(cmd->args[i], 2);
			ft_putstr_fd(": invalid parameter name\n", 2);
			code = 1;
			screen = 1;
		}
		else if (delete_var(info, cmd->args[i]) == 1)
			code = 1;
		i++;
	}
	return (code);
}
