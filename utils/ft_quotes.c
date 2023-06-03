/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 19:58:33 by ralopez-          #+#    #+#             */
/*   Updated: 2023/06/02 10:38:51 by mpizzolo         ###   ########.fr       */
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
	if (line[i] == '\'' && line[i + 1] == '\'')
		is_quote = 0;
	i++;
	i = 0;
	if (line[i] == '"' && line[i + 1] == '"')
		is_quote = 0;
	i++;
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
	len = (int)ft_strlen(line);
	result = malloc(sizeof(char) * (len + 2));
	if (!result)
		return (NULL);
	while (line[i] == quote && line[i + 1] == quote)
		i += 2;
	while (line[i] != '\0')
	{	
		result[j] = line[i];
		j++;
		i++;
	}
	while ((j - 2) > 0 && result[j - 1] == quote && result[j - 2] == quote)
		j -= 2;
	result[j] = '\0';
	if (line != NULL)
		free(line);
	return (result);
}

char	*ft_replace_double_quotes(char *line)
{
	int		i;
	char	*result;

	i = 0;
	result = ft_strdup(line);
	if (line[i] == '\'' && line[i + 1] == '\'')
	{
		while (line[i] && line[i + 1] && line[i] == line[i + 1])
		{
			result = replace_d_quotes(result, line[i]);
			i++;
		}
	}
	i = 0;
	if (line[i] == '"' && line[i + 1] == '"')
	{
		while (line[i] && line[i + 1] && line[i] == line[i + 1])
		{
			result = replace_d_quotes(result, line[i]);
			i++;
		}
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
	result = (char *)malloc(sizeof(char)
			* (ft_strlen(string) + ft_strlen(new) + 1));
	if (result == NULL)
		return (NULL);
	while (string != NULL && string[i] != '\0' && string[i] != stop)
		result[j++] = string[i++];
	if (string[i] == stop)
		i++;
	k = 0;
	while (new != NULL && new[k])
		result[j++] = new[k++];
	while (string[i] != '\0')
		result[j++] = string[i++];
	result[j] = '\0';
	free(string);
	return (result);
}
