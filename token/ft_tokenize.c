/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:41:40 by ralopez-          #+#    #+#             */
/*   Updated: 2023/06/02 12:41:50 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	store_word_aux(char *line, int *j, int *type)
{
	while (line[(*j)] && (((*type) > 1 && is_quote(line[(*j)]) != (*type))
			|| ((*type) == 0 && !is_space(line[(*j)])
				&& !is_delimiter(line[(*j)]))))
	{
		if (is_quote(line[(*j)]) > 0)
			(*type) = is_quote(line[(*j)]);
		(*j)++;
	}
	if (line[(*j)] && (*type) == 0 && is_quote(line[(*j)]) > 0)
	{
		(*type) = is_quote(line[(*j)]);
		(*j)++;
		while (line[(*j)] && is_quote(line[(*j)]) != (*type))
			(*j)++;
		if (is_quote(line[(*j)]) == (*type))
			(*type) = 0;
		(*j)++;
	}
}

int	store_word(t_inf *info, char *line, int i)
{
	int		j;
	int		type;
	char	*word;

	j = i;
	type = is_quote(line[j]);
	if (type)
		j++;
	store_word_aux(line, &j, &type);
	if (line[j] && type > 0 && !is_space(line[j]))
		type = 0 ;
	while (line[j] && !is_space(line[j]) && !is_delimiter(line[j]))
		j++;
	if (type > 0)
		j++;
	if (j > (int)ft_strlen(line))
		return (-1);
	word = ft_substr(line, i, j - i);
	ft_lstadd_back(&info->tokens, ft_lstnew(word));
	if (is_delimiter(line[j - 1]))
		return (j);
	return (j);
}

int	type_delimiter(char *line, int *i)
{
	if (line[*i] == '|')
		return (PIPE);
	else if (line[*i] == '<' && line[*i + 1] == '<')
		return (HEREDOC);
	else if (line[*i] == '>' && line[*i + 1] == '>')
		return (APPEND);
	else if (line[*i] == '<')
		return (LESS);
	else if (line[*i] == '>')
		return (GREATER);
	else if (line[*i] == '\0')
		return (END);
	return (0);
}

void	store_delimiter(t_inf *info, char *line, int *i)
{
	t_list	*tmp;

	tmp = ft_lstnew(NULL);
	tmp->type = type_delimiter(line, i);
	if (tmp->type == HEREDOC || tmp->type == APPEND)
	{
		tmp->content = ft_substr(line, *i, 2);
		*i += 1;
	}
	else
		tmp->content = ft_substr(line, *i, 1);
	*i += 1;
	ft_lstadd_back(&info->tokens, tmp);
}

int	tokenize(t_inf *info, char *line)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(line);
	while (i < len && i >= 0 && line != NULL && line[i])
	{
		if (is_space(line[i]))
			i++;
		else if (is_delimiter(line[i]))
			store_delimiter(info, line, &i);
		else
			i = store_word(info, line, i);
	}
	return (0);
}
