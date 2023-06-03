/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:41:20 by ralopez-          #+#    #+#             */
/*   Updated: 2023/06/03 15:19:11 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prepare_line(t_inf *info, char *line)
{
	if (tokenize(info, line) == -1)
		return ;
	if (check_vars(info) == -1)
		return ;
	if (delete_quotes(info) == -1)
		return ;
	if (create_commands(info) == -1)
		return ;
	free(line);
	if (info->must_continue == 1)
		info->last_code = execute_commands(info);
	ft_lstclear_cmds(info);
	ft_clear_tokens(info);
	if (info->paths != NULL)
		ft_free_split(info->paths);
}

void	display_prompt(t_inf *info)
{
	char	*line;

	line = NULL;
	info->commands = NULL;
	info->must_continue = 1;
	store_paths(info);
	set_signals_interactive();
	line = readline("minishell>");
	set_signals_noninteractive();
	if (line == NULL)
	{
		info->exit = 1;
		printf("exit\n");
		return ;
	}
	if (ft_strcmp(line, "") == 0)
		return ;
	add_history(line);
	prepare_line(info, line);
}

int	main(int argc, char *argv[], char **env)
{
	(void)argc;
	(void)argv;
	g_info.tokens = NULL;
	g_info.commands = NULL;
	g_info.pwd = NULL;
	g_info.paths = NULL;
	g_info.last_code = 0;
	g_info.env = NULL;
	g_info.exit = 0;
	store_env(&g_info, env);
	while (g_info.exit == 0)
		display_prompt(&g_info);
	end_shell(&g_info);
	return (0);
}
