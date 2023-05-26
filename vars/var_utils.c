/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 20:08:37 by ralopez-          #+#    #+#             */
/*   Updated: 2023/05/26 20:08:40 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"


int	len_var(char *tmp)
{
	int i=0;
	int len=0;

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

char *get_name(char *tmp)
{
	int		i=0;
	int		start=0;
	int		len;
	char	*res;

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
	return (res);
}

void update_status(char **str, int i, int *status)
{
	if (*status == 0 && is_quote((*str)[i]))
		(*status) = is_quote((*str)[i]);
	else if (*status == DOUBLE_QUOTE && is_quote((*str)[i]) == DOUBLE_QUOTE)
		(*status) = 0;
	else if (*status == SIMPLE_QUOTE && is_quote((*str)[i]) == SIMPLE_QUOTE)
		(*status) = 0;
}

char	*get_name_var(char *line)
{
	int	i;
	int	j;
	int	type;

	i = 0;
	j = 0;
	while (line[i] && line[i] != '$')
		i++;
	if (line[i] == '$')
		i++;
	if (line[i] == '"' || line[i] == '\'')
	{
		type = line[i];
		j = i;
		j++;
		
		while (line[j] && line[j] != type)
		{
			j++;
		}
		j++;
	}
	else
	{
		j = i;
		while (line[j] && line[j] != ' ' && line[j] != '\t' && line[j] != '$' && line[j] != '"' && line[j] != '\'')
			j++;
	}
	return (ft_substr(line, i, j - i));
}

char	*replace(char *string, char *search, char *replace)
{
	char	*result;
	int		len;
	int 	i;
	int		j;

	len = 0;
	i = 0;
	j = -1;
	len = ft_strlen(string) - ft_strlen(search) + ft_strlen(replace) + 1;
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	while (string[i] != '\0' && string[i] != '$')
	{
		result[i] = string[i];
		i++;
	}
	result[i]='\0';
	len = i;
	while (replace[++j] != '\0')
		result[i++] = replace[j];
	while (string[len] != '\0' && string[len] != ' ' && string[len] != '\'' && string[len] != '"')
		len++;
	while (string[len] != '\0')
	{
		result[i] = string[len];
		i++;
		len++;
	}
	result[i] = '\0';
	free(string);
	return (result);
}
