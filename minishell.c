/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:41:20 by ralopez-          #+#    #+#             */
/*   Updated: 2023/03/10 10:41:21 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"
/*
int	execute_builtins(t_inf *info, char *line)
{
	int	code;

	code = CMD_NOT_FOUND;
	if (ft_strcmp(line, "exit") == 0)
		exit(0);
	else if (ft_memcmp(line, "cd", 2) == 0)
		code = cd(info, line);
	else if (ft_memcmp(line, "echo", 4) == 0)
		code = echo(info, line);
	else if (ft_strcmp(line, "pwd") == 0)
		code = pwd(info);
	else if (ft_strcmp(line, "env") == 0)
		code = env(info);
	else if (ft_memcmp(line, "export", 6) == 0)
		code = export_binding(info, line);
	else if (ft_memcmp(line, "unset", 5) == 0)
		code = unset(info, line);
	return (code);
}*/




void	display_prompt(t_inf *info)
{
	char	*line;

	line = NULL;
	info->commands = NULL;
	line = readline("minishell>");
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
	if (execute_commands(info) == -1)
		return ;
	
	//int code = execute_builtins(info, line);
	free(line);
	ft_lstclear_cmds(info);
	ft_clear_tokens(info);
	
}


int	main(int argc, char *argv[], char **env)
{
	t_inf	info;

	if (1 == 2)
	{
		argc = 0;
		argv = NULL;
	}
	info.env = env;
	get_enviroment(&info);
	init_sigaction(&info);

	//last_code = 0;
	while (1)
	{
		display_prompt(&info);
	}
	exit (0);
}
