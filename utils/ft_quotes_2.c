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

int	between_simple_quotes(char *str, int index)
{
	int		x;
	int		i;
	char	quote;

	quote = '\'';
	i = index;
	x = index - 1;
	while (x >= 0)
	{
		if (str[x] == quote)
		{
			while (x >= 0)
			{
				if (str[x] == '"')
					x = -4;
				x--;
			}
			if (x != -5)
				x = -3;
			break ;
		}
		x--;
	}
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

int	is_inside_quotes(char **str, int separator)
{
	int		x;
	int		i;
	char	quote;

	i = separator;
	x = separator - 1;
	while (x >= 0)
	{
		if ((*str)[x] == '"' || (*str)[x] == '\'')
		{
			quote = (*str)[x];
			x = -3;
			break ;
		}
		x--;
	}
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

char	*ft_replace_quotes_2(char *str)
{
	char	*res;
	int		i;
	int		j;
	int		x;

	res = ft_calloc((ft_strlen(str) + 1), sizeof(char));
	i = starting_quote_from(str, &res, 0);
	if (i == -1)
		return (str);
	x = is_quote(str[i]);
	i++;
	j = i - 1;
	while (str[i])
	{
		if (!is_quote(str[i]))
			res[j++] = str[i++];
		else if (str[i])
		{
			if (x == is_quote(str[i]))
			{
				i++;
				x = is_quote(str[i]);
				while (!is_quote(str[i]) && str[i])
					res[j++] = str[i++];
				if (str[i])
					x = is_quote(str[i++]);
			}
			else
				res[j++] = str[i++];
		}
	}
	res[j] = '\0';
	free(str);
	return (res);
}
