/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:02:16 by mpizzolo          #+#    #+#             */
/*   Updated: 2023/06/02 13:24:13 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	between_simple_quotes_aux(char *str, int *x, int quote)
{
	while ((*x) >= 0)
	{
		if (str[(*x)] == quote)
		{
			while ((*x) >= 0)
			{
				if (str[(*x)] == '"')
					(*x) = -4;
				(*x)--;
			}
			if ((*x) != -5)
				(*x) = -3;
			break ;
		}
		(*x)--;
	}
}

int	between_simple_quotes(char *str, int index)
{
	int		x;
	int		i;
	char	quote;

	quote = '\'';
	i = index;
	x = index - 1;
	between_simple_quotes_aux(str, &x, quote);
	while (str[i])
	{
		if (str[i] == quote)
		{
			i = -3;
			break ;
		}
		i++;
	}
	if (x == -3 && i == -3)
		return (1);
	else
		return (0);
}

void	is_inside_quotes_aux(char **str, int *x, char *quote)
{
	while ((*x) >= 0)
	{
		if ((*str)[(*x)] == '"' || (*str)[(*x)] == '\'')
		{
			(*quote) = (*str)[(*x)];
			(*x) = -3;
			break ;
		}
		(*x)--;
	}
}

int	is_inside_quotes(char **str, int separator)
{
	int		x;
	int		i;
	char	quote;

	i = separator;
	x = separator - 1;
	is_inside_quotes_aux(str, &x, &quote);
	while ((*str)[i])
	{
		if ((*str)[i] && (*str)[i] == quote)
		{
			i = -3;
			break ;
		}
		i++;
	}
	if (x == -3 && i == -3)
		return (1);
	else
		return (0);
}

void	remove_separator(char **str, int sep)
{
	char	*res;
	int		i;
	int		j;
	char	*tmp;

	res = (char *)malloc(ft_strlen(*str) * sizeof(char));
	i = -1;
	j = 0;
	while ((*str)[++i])
	{
		if (i != sep)
		{
			res[j] = (*str)[i];
			j++;
		}
	}
	res[j] = '\0';
	tmp = *str;
	*str = res;
	free(tmp);
}
