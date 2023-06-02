/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 19:55:53 by ralopez-          #+#    #+#             */
/*   Updated: 2023/06/02 11:04:29 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/** msg:
 * This function display an error message.
 * 
 * Returns ther code that recive as argument
 */
int	msg(char *str1, char *str2, char *str3, int code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
	ft_putendl_fd(str3, 2);
	return (code);
}

int	msg_error(char *str1, char *str2, char *str3, int code)
{
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
	ft_putendl_fd(str3, 2);
	return (code);
}

void	free_memory(t_inf *info)
{
	ft_free_split(info->env);
	ft_free_split(info->paths);
	if (info->pwd != NULL)
		free(info->pwd);
	ft_clear_tokens(info);
	ft_lstclear_cmds(info);
	clear_history();
}

void	end_shell(t_inf *info)
{
	free_memory(info);
	exit(info->last_code);
}
