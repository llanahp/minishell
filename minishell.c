/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:41:20 by ralopez-          #+#    #+#             */
/*   Updated: 2023/05/19 14:51:29 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_prompt(t_inf *info)
{
	char	*line;

	line = NULL;
	info->commands = NULL;
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
	if (ft_strcmp(line, "exit") == 0)//TODO por hacer
		exit(0);//TODO mirar por si pasa el codigo con el que tiene que terminar
	add_history(line);
	if (tokenize(info, line) == -1)
		return ;
	if (check_vars(info) == -1)
		return ;
	if (delete_quotes(info) == -1)
		return ;
	if (create_commands(info) == -1)
		return ;
	info->last_code = execute_commands(info);
	free(line);
	ft_lstclear_cmds(info);
	ft_clear_tokens(info);
}


void	salida(void)
{
	system("leaks minishell");
}

int	main(int argc, char *argv[], char **env)
{
	atexit(salida);
	(void)argc;
	(void)argv;
	info.tokens = NULL;
	info.commands = NULL;
	info.pwd = NULL;
	info.paths = NULL;
	info.last_code = 0;
	info.env = NULL;
	info.exit = 0;
	get_enviroment(&info, env);
	while (info.exit == 0)
	{
		display_prompt(&info);
	}
	end_shell(&info);
	return (0);
}
