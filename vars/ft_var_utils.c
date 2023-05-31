/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_var_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 20:08:37 by ralopez-          #+#    #+#             */
/*   Updated: 2023/05/26 20:08:40 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_var(char *tmp)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (tmp[i] && tmp[i] != '$')
		i++;
	i++;
	if (ft_isdigit((int)tmp[i]) || tmp[i] == '?')
		return (1);
	while (tmp[i])
	{
		if (is_var_compliant(tmp[i]) == false)
			break ;
		i++;
		len++;
	}
	return (len);
}

char	*get_name(char *tmp)
{
	int		i;
	int		start;
	int		len;
	char	*res;

	i = 0;
	start = 0;
	while (tmp[i])
	{
		if (tmp[i] == '$')
		{
			start = i + 1;
			break ;
		}
		i++;
	}
	len = len_var(tmp);
	res = ft_substr(tmp, start, len);
	if (res != NULL && res[0] == '\0')
	{
		free(res);
		res = NULL;
	}
	return (res);
}

void	update_status(char **str, int i, int *status)
{
	if (*status == 0 && is_quote((*str)[i]))
		(*status) = is_quote((*str)[i]);
	else if (*status == DOUBLE_QUOTE && is_quote((*str)[i]) == DOUBLE_QUOTE)
		(*status) = 0;
	else if (*status == SIMPLE_QUOTE && is_quote((*str)[i]) == SIMPLE_QUOTE)
		(*status) = 0;
}
