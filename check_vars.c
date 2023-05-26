/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:08:25 by ralopez-          #+#    #+#             */
/*   Updated: 2023/05/25 12:32:10 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char	*replace_quotes(char *string, char quote)
{
	char	*result;
	int 	i;
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
	result[j]='\0';
	free(string);
	return (result);
}

char	*get_name_var(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i] && line[i] != '$')
		i++;
	if (line[i] == '$')
		i++;
	j = i;
	while (line[j] && line[j] != ' ' && line[j] != '\t' && line[j] != '$' && line[j] != '"' && line[j] != '\'')
		j++;
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

int	ft_check_smpl_and_double_quotes(char *line, t_list *tmp)
{
	int	i;
	int	is_quote;
	int	j;

	i = 0;
	is_quote = 1;
	while (line[i] && line[i] != '$' && line[i] != '"')
	{	
		if (line[i] == '\'')
			is_quote = 0;
		i++;
	}
	if (line[i] == '$')
	{	
		i++;
		if (line[i] && (line[i] == '"' || line[i] == '\''))
		{	
			is_quote = 0;
			j = 0;
			tmp->content = replace_quotes(tmp->content, '$');
		}
	}
	return (is_quote);
}

int	ft_check_char_before(char *line, char c, char z)
{
	int	i;
	int	is_quote;

	i = 0;
	is_quote = 1;
	while (line[i] && line[i] != z)
	{	
		if (line[i] == c)
			is_quote = 0;
		i++;
	}
	return (is_quote);
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

char *replace_d_quotes(char *line, char quote)
{
    int i, j;
    int len = strlen(line);
    char *result = malloc(len + 1);
    
    i = 0;
    j = 0;
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
    return result;
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

int	check_vars(t_inf *info)
{
	t_list	*tmp;
	char	*var;
	char	 *name;

	tmp = info->tokens;
	while (tmp)
	{
		if (!ft_are_double_quotes(tmp->content))
		{
			tmp->content = ft_replace_double_quotes(tmp->content);
			tmp = info->tokens;
		}
		if (ft_strcontains(tmp->content, '$') && ft_check_smpl_and_double_quotes(tmp->content, tmp))
		{
			name = get_name_var(tmp->content);
			var = get_var(info, name);
			if (var == NULL)
				tmp->content = replace(tmp->content, name, "");
			else
				tmp->content = replace(tmp->content, name, var);
			free(name);
			tmp = info->tokens;
		}
		else if (ft_strcontains(tmp->content, '~') && ft_check_char_before(tmp->content, '\'', '~') && ft_check_char_before(tmp->content, '"', '~'))
		{
			var = get_var(info, "USER_ZDOTDIR");
			tmp->content = replace(tmp->content, "~", var);
			tmp->content = replace_quotes(tmp->content, '~');
			tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
	//mostrar_tokens2(info);
	return (0);
}

/*
caso de prueba:
hola que tal | pers < ddfasddf> || "yes" 'per"otro"o' esto
*/

int	delete_quotes(t_inf *info)
{
	t_list	*tmp;
	char	*temp;

	tmp = info->tokens;
	temp = NULL;
	while (tmp)
	{
		if (ft_strcontains(tmp->content, '"') && ft_check_char_before(tmp->content, '\'', '"') && temp != tmp->content)
		{
			// if (ft_check_char_before(tmp->content, '\''))
			tmp->content = replace_quotes(tmp->content, '\"');
			temp = tmp->content;
			tmp = info->tokens;
		}
		else if (ft_strcontains(tmp->content, '\'') && temp != tmp->content)
		{	
			tmp->content = replace_quotes(tmp->content, '\'');
			temp = tmp->content;
			tmp = info->tokens;
		}
		else
			tmp = tmp->next;
	}
//	mostrar_tokens2(info);
	return (0);
}
// && ft_check_char_before(tmp->content, '\'')