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

int	ft_check_smpl_and_double_quotes(char *line, t_list *tmp)
{
	int	i;
	int	is_quote;

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



static bool	is_separator(char c)
{
	if (c == '$' || c == ' ' || c == '=' || c == '\0')
		return (1);
	else
		return (0);
}
bool	is_var_compliant(char c)
{
	if (ft_isalnum(c) == 0 && c != '_')
		return (false);
	else
		return (true);
}

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

/**
 * between_quotes:
 *  Returns 1 if it is, 0 if it is not
 * 
 */
int between_quotes(char *str, int i)
{
	if (i > 0)
	{
		if (is_quote(str[i - 1]) == DOUBLE_QUOTE && is_quote(str[i + 1]) == DOUBLE_QUOTE)
			return (1);
	}
	return (0);
}

void	replace_for_var(char **str, char *value, int index)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new  = (char *)malloc(sizeof(char) * (ft_strlen((*str) + ft_strlen(value) + 1)) + 1);
	if (!new)
		return ;
	while ((*str)[i])
	{
		if ((*str)[i] == '$' && i == index)
		{
			int h=0;
			while (value[h])
			{
				new[j++] = value[h++];
			}
			i = i + len_var((*str) + index) + 1;
			if ((*str)[i] == '\0')
				break ;
		}
		new[j++] = (*str)[i++];
	}
	new[j] = '\0';
	free((*str));
	(*str) = new;
}


void	replace_for_null(char **str,  int index)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new  = (char *)malloc(sizeof(char) * (ft_strlen((*str) + 1)) + 1);
	if (!new)
		return ;
	while ((*str)[i])
	{
		if ((*str)[i] == '$' && i == index)
		{
			i = i + len_var((*str) + index) + 1;
			if ((*str)[i] == '\0')
				break ;
		}
		new[j++] = (*str)[i++];
	}
	new[j] = '\0';
	free((*str));
	(*str) = new;
}

void replace_var(char **str, int i, t_inf *info)
{
	char *var;
	char *value;

	var = get_name(*str + i);
	value  = get_var(info, var);
	if (value != NULL)
		replace_for_var(str, value, i);
	else
		replace_for_null(str, i);
}

void extend_var(char **str,t_inf *info)
{
	int	i;
	int	status = 0;

	i = 0;
	while ((*str)[i])
	{
		update_status(str, i, &status);
		if ((*str)[i] == '$' && (status == 0 || status == DOUBLE_QUOTE) && is_separator((*str)[i + 1]) == 0 && between_quotes((*str), i) == 0 && (*str)[i + 1] != '"')
		{
			replace_var(str, i ,info);
		}
		else
			i++;
	}
}

int	check_vars(t_inf *info)
{
	t_list	*tmp;
	char	*var;

	tmp = info->tokens;
	while (tmp)
	{
		if (!ft_are_double_quotes(tmp->content))
		{
			tmp->content = ft_replace_double_quotes(tmp->content);
			tmp = info->tokens;
		}
		
		if (ft_strcontains(tmp->content, '$'))//&& ft_check_smpl_and_double_quotes(tmp->content, tmp))
		{
			extend_var(&tmp->content, info);			
		}
		else if (ft_strcontains(tmp->content, '~') && ft_check_char_before(tmp->content, '\'', '~') && ft_check_char_before(tmp->content, '"', '~'))
		{
			var = get_var(info, "USER_ZDOTDIR");
			tmp->content = replace(tmp->content, "~", var);
			tmp->content = replace_quotes(tmp->content, '~');
			
		}
		
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