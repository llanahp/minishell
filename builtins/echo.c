/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:33:39 by ralopez-          #+#    #+#             */
/*   Updated: 2023/06/03 16:05:13 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_str_contains_n(char *str)
{
	int		res;
	int		i;
	size_t	len;

	res = 1;
	i = 0;
	len = ft_strlen(str);
	while (i < (int)len - 1 && str != NULL && res)
	{
		if (str[i] == '-' && str[i + 1] == 'n')
			res = 0;
		i++;
	}
	return (res);
}

int	checking_flag_n(char **str, int *i)
{
	int	is_n;

	is_n = 0;
	if (str != NULL && !ft_str_contains_n(str[*i]))
	{
		is_n = 1;
		(*i)++;
		while (str != NULL && !ft_str_contains_n(str[*i]))
			(*i)++;
	}
	return (is_n);
}

int	echo(t_command *cmd)
{
	int	i;
	int	is_n;
	int	fd_write;

	i = 0;
	is_n = 0;
	fd_write = 1;
	if (cmd->output != -2)
		fd_write = cmd->output;
	if (!cmd->args[i])
	{
		ft_putstr_fd("\n", fd_write);
		return (0);
	}
	is_n = checking_flag_n(cmd->args, &i);
	while (cmd != NULL && cmd->args[i] != NULL && cmd->args && cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], fd_write);
		if (cmd->args[i + 1])
			ft_putstr_fd(" ", fd_write);
		i++;
	}
	if (!is_n)
		ft_putstr_fd("\n", fd_write);
	return (0);
}
