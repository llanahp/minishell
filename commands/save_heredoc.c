/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:08:25 by ralopez-          #+#    #+#             */
/*   Updated: 2023/03/31 14:08:27 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	read_heredoc_aux(char **buf, char *delimiter, int fd)
{
	if ((*buf) != NULL)
		(*buf)[ft_strlen((*buf))] = '\0';
	if ((*buf) == NULL)
		(*buf) = ft_strdup(delimiter);
	(*buf) = ft_replace_quotes_2(buf);
	if (ft_strcmp((*buf), delimiter) == 0)
	{
		if ((*buf) != NULL)
			free((*buf));
		(*buf) = NULL;
		return (1);
	}
	ft_putendl_fd((*buf), fd);
	if ((*buf) != NULL)
		free((*buf));
	(*buf) = NULL;
	return (0);
}

int	read_heredoc(char *name, char *delimiter, t_inf *info)
{
	char	*buf;
	int		fd;

	fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (fd < 0)
		return (msg("here_doc", ": ", strerror(errno), -1));
	while (1 == 1)
	{
		buf = NULL;
		buf = readline("heredoc>");
		if (info->must_continue == 0
			|| read_heredoc_aux(&buf, delimiter, fd) == 1)
		{
			if (buf != NULL)
				free(buf);
			break ;
		}
		free(buf);
	}
	close (fd);
	return (0);
}

void	name_hd2(t_command *command, char *name, char *delimiter, t_inf *info)
{
	if (command->input_name != NULL)
		free(command->input_name);
	command->input_name = ft_strdup(name);
	if (name != NULL)
		free(name);
	if (delimiter != NULL)
		free(delimiter);
	command->input = open(command->input_name, O_RDONLY);
	if (command->input == -1)
	{
		msg(command->input_name, ": ", strerror(errno), 0);
		info->last_code = 1;
		info->must_continue = 0;
	}
}

t_list	*set_name_heredoc(t_list *tmp, t_command *command, t_inf *info)
{
	char	*name;
	char	*delimiter;
	int		i;

	i = 0;
	name = find_name();
	tmp = tmp->next;
	delimiter = define_delimiter(&tmp);
	if (delimiter == NULL)
	{
		if (name != NULL)
			free(name);
		info->last_code = msg("heredoc", ": ", "syntax error", 258);
		return (NULL);
	}
	command->input_name = ft_strdup(name);
	heredoc_fork(info, command, delimiter);
	name_hd2(command, name, delimiter, info);
	return (tmp);
}

t_list	*save_heredoc(t_inf *info, t_list *tmp)
{
	t_command	*command;

	if (ft_error_syntax (tmp, info) == 1)
		return (NULL);
	command = get_last_cmd(info);
	close_prev_redir(command);
	tmp = set_name_heredoc(tmp, command, info);
	set_signals_noninteractive();
	return (tmp);
}
