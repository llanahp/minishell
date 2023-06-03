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

int	file_exists(char *name)
{
	if (access(name, F_OK) == 0)
		return (1);
	else
		return (0);
}

char	*define_delimiter_aux(char **delimiter, t_list **tmp)
{
	int		quote;

	quote = (*tmp)->type;
	(*tmp) = (*tmp)->next;
	while ((*tmp) && (*tmp)->type != quote)
	{
		(*delimiter) = ft_strjoin((*delimiter), (*tmp)->content);
		(*tmp) = (*tmp)->next;
	}
	if ((*tmp)->type != quote)
	{
		free((*delimiter));
		return (NULL);
	}
	return ((*delimiter));
}

char	*define_delimiter(t_list **tmp)
{
	char	*delimiter;

	if (!(*tmp))
		return (NULL);
	if ((*tmp)->type == WORD)
	{
		delimiter = ft_strdup((*tmp)->content);
		(*tmp) = (*tmp)->next;
		return (delimiter);
	}
	else if ((*tmp)->type == SIMPLE_QUOTE || (*tmp)->type == DOUBLE_QUOTE)
		return (define_delimiter_aux(&delimiter, tmp));
	else
		return (NULL);
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
		set_signals_interactive_here();
		buf = readline("heredoc>");
		set_signals_noninteractive();
		if (info->must_continue == 0)
		{
			free(buf);
			break ;
		}
		if (buf != NULL)
			buf[ft_strlen(buf)] = '\0';
		if (buf == NULL)
			buf = ft_strdup(delimiter);
		buf = check_var_replace(buf, info);
		buf = ft_replace_quotes_2(buf);
		if (ft_strcmp(buf, delimiter) == 0)
		{
			free(buf);
			break ;
		}
		ft_putendl_fd(buf, fd);
		free(buf);
	}
	close (fd);
	return (0);
}

t_list	*set_name_heredoc(t_list *tmp, t_command *command, t_inf *info)
{
	char	*name;
	char	*delimiter;
	int		i;

	i = 0;
	while (file_exists(ft_strjoin("/tmp/heredoc_", ft_itoa(i))))
		i++;
	name = ft_strjoin("/tmp/heredoc_", ft_itoa(i));
	tmp = tmp->next;
	delimiter = define_delimiter(&tmp);
	if (read_heredoc(name, delimiter, info) == -1)
		return (NULL);
	command->input_name = ft_strdup(name);
	free(name);
	free(delimiter);
	command->input = open(command->input_name, O_RDONLY);
	if (command->input == -1)
	{
		msg(command->input_name, ": ", strerror(errno), 0);
		info->last_code = 1;
		info->must_continue = 0;
	}
	return (tmp);
}

t_list	*save_heredoc(t_inf *info, t_list *tmp)
{
	t_command	*command;

	command = get_last_cmd(info);
	close_prev_redir(command);
	tmp = set_name_heredoc(tmp, command, info);
	return (tmp);
}
