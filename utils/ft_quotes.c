/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 19:58:33 by ralopez-          #+#    #+#             */
/*   Updated: 2023/05/26 19:58:34 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*replace_quotes(char *string, char quote)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = (char *)malloc(sizeof(char) * (ft_strlen(string) - 1 + 1));
	if (result == NULL)
		return (NULL);
	while (string[i] != '\0')
	{
		if (string[i] != quote)
		{
			result[j] = string[i];
			j++;
		}
		i++;
	}
	result[j] = '\0';
	free(string);
	return (result);
}

int	ft_are_double_quotes(char *line)
{
	int	i;
	int	is_quote;

	i = 0;
	is_quote = 1;
	while (line[i])
	{	
		if (line[i] == '\'' && line[i + 1] == '\'')
			is_quote = 0;
		i++;
	}
	i = 0;
	while (line[i])
	{	
		if (line[i] == '"' && line[i + 1] == '"')
			is_quote = 0;
		i++;
	}
	return (is_quote);
}

char	*replace_d_quotes(char *line, char quote)
{
	int		i;
	int		j;
	int		len;
	char	*result;

	i = 0;
	j = 0;
	len = strlen(line);
	result = malloc(len + 1);
	while (line[i])
	{
		if (line[i] == quote && line[i + 1] == quote)
			i += 2;
		result[j] = line[i];
		i++;
		j++;
	}
	result[j] = '\0';
	free(line);
	return (result);
}

char	*ft_replace_double_quotes(char *line)
{
	int		i;
	char	*result;

	i = 0;
	result = ft_strdup(line);
	while (line[i])
	{	
		if (line[i] == '\'' && line[i + 1] == '\'')
			result = replace_d_quotes(result, '\'');
		i++;
	}
	i = 0;
	while (line[i])
	{	
		if (line[i] == '"' && line[i + 1] == '"')
			result = replace_d_quotes(result, '"');
		i++;
	}
	return (result);
}

char	*replace_string(char *string, char stop, char *new)
{
	char	*result;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	result = (char *)malloc(sizeof(char) * (ft_strlen(string) + ft_strlen(new) + 1));
	if (result == NULL)
		return (NULL);
	while (string[i] != '\0' && string[i] != stop)
	{
		result[j] = string[i];
		j++;
		i++;
	}
	if (string[i] == stop)
		i++;
	k = 0;
	while (new[k])
	{
		result[j] = new[k];
		j++;
		k++;
	}
	while (string[i] != '\0')
	{
		result[j] = string[i];
		j++;
		i++;
	}
	result[j] = '\0';
	free(string);
	return (result);
}
