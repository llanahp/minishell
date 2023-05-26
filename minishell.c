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

# include "minishell.h"


 t_inf info;

void	display_prompt(t_inf *info)
{
	char	*line;

	line = NULL;
	info->commands = NULL;
	set_signals_interactive();
	line = readline("minishell>");
	set_signals_noninteractive();
	if (ft_strcmp(line, "") == 0)
		return ;
	if (ft_strcmp(line, "exit") == 0)
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
	info->last_code  = execute_commands(info);
	free(line);
	ft_lstclear_cmds(info);
	ft_clear_tokens(info);
	
}


int	main(int argc, char *argv[], char **env)
{
	if (1 == 2)
	{
		argc = 2;
		argv =  NULL;
	}
	info.tokens = NULL;
	info.commands = NULL;
	info.pwd = NULL;
	info.paths = NULL;
	info.last_code = 0;
	info.env = NULL;
		get_enviroment(&info, env);

	while (1)
	{
		display_prompt(&info);
	}
	end_shell(&info, info.last_code);
	return (0);
}