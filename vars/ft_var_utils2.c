/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_var_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 15:31:56 by ralopez-          #+#    #+#             */
/*   Updated: 2023/05/27 15:31:57 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_counters(char *line, int	*i)
{
	while (line[(*i)] && line[(*i)] != '$')
		(*i)++;
	if (line[(*i)] == '$')
		(*i)++;
}

char	*get_name_var(char *line)
{
	int	i;
	int	j;
	int	type;

	i = 0;
	j = 0;
	type = 0;
	update_counters(line, &i);
	if (line[i] == '"' || line[i] == '\'')
	{
		type = line[i];
		j = i;
		j++;
		while (line[j] && line[j] != type)
			j++;
		j++;
	}
	else
	{
		j = i;
		while (line[j] && line[j] != ' ' && line[j] != '\t' && line[j] != '$'
			&& line[j] != '"' && line[j] != '\'')
			j++;
	}
	return (ft_substr(line, i, j - i));
}

void	copy_content(int *i, int *len, char *result, char *string)
{
	while (string[(*i)] != '\0' && string[(*i)] != '$')
	{
		result[(*i)] = string[(*i)];
		i++;
	}
	result[(*i)] = '\0';
	(*len) = (*i);
}

void	copy_content2(int *i, int *len, char *result, char *string)
{
	while (string[(*len)] != '\0')
	{
		result[(*i)] = string[(*len)];
		(*i)++;
		(*len)++;
	}
	result[(*i)] = '\0';
}

char	*replace(char *string, char *search, char *replace)
{
	char	*result;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = -1;
	len = ft_strlen(string) - ft_strlen(search) + ft_strlen(replace) + 1;
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	copy_content(&i, &len, result, string);
	while (replace[++j] != '\0')
		result[i++] = replace[j];
	while (string[len] != '\0' && string[len] != ' ' && string[len]
		!= '\'' && string[len] != '"')
		len++;
	copy_content2(&len, &i, result, string);
	free(string);
	return (result);
}
