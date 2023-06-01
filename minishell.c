/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:41:20 by ralopez-          #+#    #+#             */
/*   Updated: 2023/06/01 12:57:07 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* GNL */

char	*ft_strjoin_asco_free(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1)
	{
		s1 = malloc(1);
		s1[0] = '\0';
	}
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i] != '\0')
		str[i] = s1[i];
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

char	*ft_line_cut(char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	tmp = malloc(i + 2);
	if (!tmp)
		return (NULL);
	tmp[i++] = '\0';
	i = -1;
	while (str[++i] && str[i] != '\n')
		tmp[i] = str[i];
	tmp[i] = str[i];
	tmp[++i] = '\0';
	return (tmp);
}

char	*ft_rest_str(char *str)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	tmp = malloc(ft_strlen(str) - i + 1);
	if (!tmp)
		return (NULL);
	i++;
	j = 0;
	while (str[i])
		tmp[j++] = str[i++];
	tmp[j] = '\0';
	free(str);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;
	char		tmp[10];
	int			nb;
	int			i;

	nb = 1;
	i = 0;
	while (nb != 0)
	{
		nb = read(fd, tmp, 9);
		if (nb == -1)
			free(str);
		if (nb == -1)
			return (str = NULL);
		tmp[nb] = '\0';
		str = ft_strjoin_asco_free(str, tmp);
		while (tmp[i] != '\n' && tmp[i] != '\0')
			i++;
		if (tmp[i] == '\n')
			break ;
	}
	line = ft_line_cut(str);
	str = ft_rest_str(str);
	return (line);
}

void	ft_delete_char(char *str)
{
	while (*str != '\0')
	{
		*str = *(str + 1);
		str++;
	}
}

/* GNL */




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
	info->last_code = execute_commands(info);
	free(line);
	ft_lstclear_cmds(info);
	ft_clear_tokens(info);
}

void	prompt_tester(t_inf *info)
{
	char	*line;

	line = NULL;
	info->commands = NULL;

	// set_signals_interactive();
	// line = readline("minishell>");
	line = get_next_line(STDIN_FILENO);
	if (ft_strchr(line, '\n') > 0)
		ft_delete_char(ft_strchr(line, '\n'));
	// set_signals_noninteractive();
	if (line == NULL)
	{
		info->exit = 1;
		printf("exit\n");
		return ;
	}
	if (ft_strcmp(line, "") == 0)
		return ;
	// add_history(line);
	prepare_line(info, line);
}

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
	add_history(line);
	prepare_line(info, line);
}

void	salida(void)
{
	system("leaks -q minishell");
}

void	find_pid(t_inf *info)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	else if (pid == 0)
	{
		exit(0);
	}
	else
		info->minishell_pid = (int)getpid();
	waitpid(-1, &status, 0);
}

int	main(int argc, char *argv[], char **env)
{
	//atexit(salida);
	(void)argc;
	(void)argv;
	g_info.tokens = NULL;
	g_info.commands = NULL;
	g_info.pwd = NULL;
	g_info.paths = NULL;
	g_info.last_code = 0;
	g_info.env = NULL;
	g_info.exit = 0;
	find_pid(&g_info);
	get_enviroment(&g_info, env);
	while (g_info.exit == 0)
		display_prompt(&g_info);
	end_shell(&g_info);
	return (0);
}
