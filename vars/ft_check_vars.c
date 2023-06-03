/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_vars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:08:25 by ralopez-          #+#    #+#             */
/*   Updated: 2023/06/02 13:21:50 by mpizzolo         ###   ########.fr       */
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

void	simple_extend_var(char **str, int *i, t_inf *info)
{
	if ((*str)[(*i)] == '$' && (*str)[(*i) + 1] == '?')
		replace_for_var(str, ft_itoa(info->last_code), (*i));
}

void	extend_var_aux(int *i, int len, char **str)
{
	if (((*i) + 1) < len && (*str)[(*i)] == '$'
		&& !ft_isalpha((*str)[(*i) + 1]) && !is_inside_quotes(str, (*i)))
	{
		remove_separator(str, (*i));
		(*i)++;
	}
	else
		(*i)++;
}

void	extend_var(char **str, t_inf *info)
{
	int	i;
	int	status;
	int	len;

	i = 0;
	status = 0;
	len = ft_strlen(*str);
	while (i < len && str != NULL && (*str) != NULL && (*str)[i])
	{
		len = ft_strlen(*str);
		update_status(str, i, &status);
		if (between_simple_quotes(*str, i) == 0)
			simple_extend_var(str, &i, info);
		if ((i + 1) < len && (*str)[i] == '$'
			&& (status == 0 || status == DOUBLE_QUOTE)
			&& is_separator((*str)[i + 1]) == 0
			&& between_quotes((*str), i) == 0
			&& (*str)[i + 1] != '"')
		{
			if (replace_var(str, i, info) == -1)
				i++;
		}
		else
			extend_var_aux(&i, len, str);
	}
}
