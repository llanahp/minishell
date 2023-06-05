/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:43:45 by ralopez-          #+#    #+#             */
/*   Updated: 2023/06/03 15:43:46 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	starting_quote_from(char *str, char **res, int i)
{
	while (str[i])
	{
		if ((str[i] == '"') || (str[i] == '\''))
			return (i);
		else
			(*res)[i] = str[i];
		i++;
	}
	return (-1);
}

void	ft_replace_quotes_aux(char *str, char **res, int i, int x)
{
	int	j;

	j = i - 1;
	while (str[i])
	{
		if (!is_quote(str[i]))
			(*res)[j++] = str[i++];
		else if (str[i])
		{
			if (x == is_quote(str[i]))
			{
				i++;
				x = is_quote(str[i]);
				while (!is_quote(str[i]) && str[i])
					(*res)[j++] = str[i++];
				if (str[i])
					x = is_quote(str[i++]);
			}
			else
				(*res)[j++] = str[i++];
		}
	}
	(*res)[j] = '\0';
}

char	*ft_replace_quotes_2(char **str)
{
	char	*res;
	int		i;
	int		j;
	int		x;

	res = ft_calloc((ft_strlen((*str)) + 1), sizeof(char));
	if (!res)
		return (NULL);
	i = starting_quote_from((*str), &res, 0);
	if (i == -1)
	{
		free(res);
		res = ft_strdup((*str));
		if ((*str))
			free((*str));
		str = NULL;
		return (res);
	}
	x = is_quote((*str)[i]);
	i++;
	j = i - 1;
	ft_replace_quotes_aux((*str), &res, i, x);
	if ((*str))
		free((*str));
	return (res);
}
