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
	clear_history();
	if (info->env != NULL)
		ft_free_split(info->env);
	if (info->paths != NULL)
		ft_free_split(info->paths);
	if (info->pwd != NULL)
		free(info->pwd);
	ft_clear_tokens(info);
	ft_lstclear_cmds(info);
}

void	end_shell(t_inf *info)
{
	free_memory(info);
	exit(info->last_code);
}

int	ft_error_syntax(t_list *tmp, t_inf *info)
{
	if (tmp->content != NULL && tmp->next != NULL && tmp->next->content != NULL
		&& ft_strcmp(tmp->content, tmp->next->content) == 0)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(tmp->content, 2);
		ft_putstr_fd("'\n", 2);
		info->last_code = 258;
		info->must_continue = 0;
		return (1);
	}
	return (0);
}
