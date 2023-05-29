/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 19:51:58 by ralopez-          #+#    #+#             */
/*   Updated: 2023/05/26 19:51:59 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	is_delimiter(char c)
{
	if (c == '|' || c == '<' || c == '>')
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
