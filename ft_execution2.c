/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 12:54:48 by ralopez-          #+#    #+#             */
/*   Updated: 2023/06/03 12:54:49 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	num_cmds(t_inf *info)
{
	int			i;
	t_command	*aux;

	i = 0;
	aux = info->commands;
	while (aux)
	{
		i++;
		aux = aux->next;
	}
	return (i);
}

/** create_cmd:
 * This function create the string with the command to execute
 * Desalocates the memory that dont use.
 */
char	*create_cmd(t_inf *info, int i, char *cmd)
{
	char	*cmd2;
	char	*res;

	cmd2 = ft_strjoin(info->paths[i], "/");
	res = ft_strjoin(cmd2, cmd);
	free(cmd2);
	return (res);
}

char	*look_in_path(t_inf *info, char *cmd)
{
	char	*cmd_ret;
	int		i;

	i = -1;
	while (info->paths[++i] != NULL)
	{
		cmd_ret = create_cmd(info, i, cmd);
		if (access(cmd_ret, F_OK | X_OK) == 0)
			break ;
		free(cmd_ret);
		cmd_ret = NULL;
	}
	return (cmd_ret);
}

char	*get_path(char *cmd, t_inf *info)
{
	char	*cmd_ret;

	if (cmd == NULL || cmd[0] == '\0')
		return (NULL);
	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	if (info->paths == NULL)
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (cmd);
		free(cmd);
		return (NULL);
	}
	cmd_ret = look_in_path(info, cmd);
	free(cmd);
	return (cmd_ret);
}

int	display_error_path(char *cmd_original)
{
	if (g_info.paths == NULL)
		return (msg(cmd_original, NOFILE, "", 127));
	else
		return (msg(cmd_original, NOCMD, "", 127));
}
