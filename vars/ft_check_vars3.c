/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_vars3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 12:18:52 by ralopez-          #+#    #+#             */
/*   Updated: 2023/06/03 12:18:53 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_var_replace(char *str, t_inf *info)
{
	char	*var;
	char	*temp;

	if (ft_strcontains(str, '$')
		&& !between_simple_quotes(str, ft_strichr(str, '$')))
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
		tmp->content = ft_replace_quotes_2(&tmp->content);
		tmp = tmp->next;
	}
	return (0);
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
