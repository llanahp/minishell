/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_vars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:08:25 by ralopez-          #+#    #+#             */
/*   Updated: 2023/05/25 12:32:10 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_char_before(char *line, char c, char z)
{
	int	i;
	int	is_quote;

	i = 0;
	is_quote = 1;
	while (line[i] && line[i] != z)
	{	
		if (line[i] == c)
			is_quote = 0;
		i++;
	}
	return (is_quote);
}

/**
 * between_quotes:
 *  Returns 1 if it is, 0 if it is not
 * 
 */
int	between_quotes(char *str, int i)
{
	if (i > 0)
	{
		if (is_quote(str[i - 1]) == DOUBLE_QUOTE
			&& is_quote(str[i + 1]) == DOUBLE_QUOTE)
			return (1);
	}
	return (0);
}

void	extend_var(char **str, t_inf *info)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while ((*str)[i])
	{
		update_status(str, i, &status);
		if ((*str)[i] == '$' && (*str)[i + 1] == '?')
			replace_for_var(str, ft_itoa(info->last_code), i);
		if ((*str)[i] == '$' && (status == 0 || status == DOUBLE_QUOTE)
			&& is_separator((*str)[i + 1]) == 0
			&& between_quotes((*str), i) == 0
			&& (*str)[i + 1] != '"')
		{
			replace_var(str, i, info);
		}
		else
			i++;
	}
}

int	check_vars(t_inf *info)
{
	t_list	*tmp;
	char	*var;

	tmp = info->tokens;

	while (tmp != NULL)
	{
		if (!ft_are_double_quotes(tmp->content))
		{
			tmp->content = ft_replace_double_quotes(tmp->content);
			tmp = info->tokens;
		}
		if (ft_strcontains(tmp->content, '$'))
			extend_var(&tmp->content, info);
		else if (ft_strcontains(tmp->content, '~')
			&& ft_check_char_before(tmp->content, '\'', '~')
			&& ft_check_char_before(tmp->content, '"', '~'))
		{
			var = get_var(info, "USER_ZDOTDIR");
			tmp->content = replace_string(tmp->content, '~', var);
		}	
		tmp = tmp->next;
	}
	return (0);
}

int	delete_quotes(t_inf *info)
{
	t_list	*tmp;
	char	*temp;

	tmp = info->tokens;
	temp = NULL;
	while (tmp)
	{
		if (ft_strcontains(tmp->content, '"')
			&& ft_check_char_before(tmp->content, '\'', '"')
			&& temp != tmp->content)
		{
			tmp->content = replace_quotes(tmp->content, '\"');
			temp = tmp->content;
			tmp = info->tokens;
		}
		else if (ft_strcontains(tmp->content, '\'') && temp != tmp->content)
		{	
			tmp->content = replace_quotes(tmp->content, '\'');
			temp = tmp->content;
			tmp = info->tokens;
		}
		else
			tmp = tmp->next;
	}
	return (0);
}
