/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 19:55:53 by ralopez-          #+#    #+#             */
/*   Updated: 2023/05/26 19:55:54 by ralopez-         ###   ########.fr       */
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

void	end_shell(t_inf *info)
{
	if (1 == 2)
		info = NULL;
	//ft_lstclear_cmds(info);
	//ft_lstclear_tokens(info);
	//ft_free_array(info->paths);
	//ft_free_array(info->env);
	exit(0);
} 
