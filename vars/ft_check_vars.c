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
	/*if ((*str)[(*i)] == '$' && (*str)[(*i) + 1] == '$')
	{
		replace_for_var(str, ft_itoa(info->minishell_pid), (*i));
	}*/
	if ((*str)[(*i)] == '$' && (*str)[(*i) + 1] == '?')
		replace_for_var(str, ft_itoa(info->last_code), (*i));
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
		if ((i + 1) < len && (*str)[i] == '$' && (status == 0 || status == DOUBLE_QUOTE)
			&& is_separator((*str)[i + 1]) == 0
			&& between_quotes((*str), i) == 0
			&& (*str)[i + 1] != '"')
		{
			if (replace_var(str, i, info) == -1)
				i++;
		}
		else if ((i + 1) < len && (*str)[i] == '$' && !ft_isalpha((*str)[i + 1]) && !is_inside_quotes(str, i))
		{
			remove_separator(str, i);
			i++;
		}
		else
			i++;
	}
}

int	expand_pox(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '~')
		i++;
	if (str[i + 1] == '/' || str[i + 1] == '\0')
		return (1);
	return (0);
}

char	*check_var_replace(char *str, t_inf *info)
{
	char	*var;
	char	*temp;

	if (ft_strcontains(str, '$') && !between_simple_quotes(str, ft_strichr(str, '$')))
		extend_var(&str, info);
	else if (ft_strcontains(str, '~')
		&& ft_check_char_before(str, '\'', '~')
		&& ft_check_char_before(str, '"', '~'))
	{
		if (expand_pox(str) == 1)
		{
			var = get_var(info, "USER_ZDOTDIR");
			str = replace_string(str, '~', var);
		}
	}
	temp = ft_strdup(str);
	if (str != NULL)
		free(str);
	return (temp);
}

int	check_vars(t_inf *info)
{
	t_list	*tmp;

	tmp = info->tokens;
	while (tmp != NULL)
	{
		if (!ft_are_double_quotes(tmp->content))
		{
			tmp->content = ft_replace_double_quotes(tmp->content);
			tmp = info->tokens;
		}
		tmp->content = check_var_replace(tmp->content, info);	
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
		if (ft_strcontains(tmp->content, '\'')
			|| ft_strcontains(tmp->content, '"'))
		tmp->content = ft_replace_quotes_2(tmp->content);
		tmp = tmp->next;
		
	}
	return (0);
}

