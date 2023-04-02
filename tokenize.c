/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:41:40 by ralopez-          #+#    #+#             */
/*   Updated: 2023/03/31 10:41:42 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

//temporal ||  &&  
int	is_delimiter(char c)
{
	if (c == '|' || c == ';' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	is_quote(char c)
{
	if (c == '"')
		return (DOUBLE_QUOTE);
	if (c == '\'')
		return (SIMPLE_QUOTE);
	return (0);
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
	while (line[j] && ((type > 1 && is_quote(line[j]) != type)
			|| (type == 0 && !is_space(line[j]))))
		j++;
	if (line[j] && type > 0 && !is_space(line[j]))
		type = 0 ;
	while(line[j] && !is_space(line[j]))
		j++;
	if (type > 0)
		j++;

	if (j > (int)ft_strlen(line))
		return (-1);
	word = ft_substr(line, i, j - i);
	ft_lstadd_back(&info->tokens, ft_lstnew(word));
	return (j);
}

void mostrar_tokens(t_inf *info)
{
	printf("--------------\n");
	while (info->tokens)
	{
		printf("%s\n", (char *)info->tokens->content);
		info->tokens = info->tokens->next;
	}
}

int	type_delimiter(char *line, int *i) 
{
	if (line[*i] == '|')
		return (PIPE);
	else if (line[*i] == ';')
		return (SEMICOLON);
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

	i = 0;
	while (line[i])
	{
		if (is_space(line[i]))
			i++;
		else if (is_delimiter(line[i]))
		{
			store_delimiter(info, line, &i);
		}
		else
		{
			i = store_word(info, line, i);
		}
	}
	return (0);
}