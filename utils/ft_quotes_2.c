/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:02:16 by mpizzolo          #+#    #+#             */
/*   Updated: 2023/05/31 19:02:33 by mpizzolo         ###   ########.fr       */
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

char	*ft_replace_quotes_2(char *str)
{
	char	*res;
	int		i;
	int		j;
	int		x;

	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	i = starting_quote_from(str, &res, 0);
	
	if (i == -1)
		return (str);
	x = is_quote(str[i]);
	j = i;
	while (str[i])
	{
		if (!is_quote(str[i]))
		{
			res[j] = str[i];
			j++;
			i++;
		}
		else if (str[i])
		{
			if (x == is_quote(str[i]))
			{
				i++;
				x = is_quote(str[i]);
				while (!is_quote(str[i]) && str[i])
				{
					res[j] = str[i];
					j++;
					i++;
				}
				if (str[i])
				{
					x = is_quote(str[i]);
					i++;
				}
			}
			else
			{
				res[j] = str[i];
				j++;
				i++;
			}
		}
	}
	res[j] = '\0';
	return (res);
}
