/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:08:25 by ralopez-          #+#    #+#             */
/*   Updated: 2023/05/25 02:19:44 by mpizzolo         ###   ########.fr       */
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
	while (string[len] != '\0' && string[len] != ' ')
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
// este caso no funciona bien, y muchos mas asi parecidos
// bash$ echo "'$USER'"  >> devuelve >> 'mpizzolo' >> minishell >> devuelve mpizzolo
// bash$ echo '"$USER"'  >> devuelve >> "$USER" >> minishell >> $USER
// bash$ echo "$"HOME"" >> devuelve >> $HOME >> minishell >> cualq cosa

int	check_vars(t_inf *info)
{
	t_list	*tmp;
	char	*var;
	char	 *name;

	tmp = info->tokens;
	while (tmp)
	{
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
		else if (ft_strcontains(tmp->content, '~'))
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

	tmp = info->tokens;
	while (tmp)
	{
		if (ft_strcontains(tmp->content, '"'))
		{
			tmp->content = replace_quotes(tmp->content, '\"');
			tmp = info->tokens;
		}
		else if (ft_strcontains(tmp->content, '\''))
		{
			tmp->content = replace_quotes(tmp->content, '\'');
			tmp = info->tokens;
		}
		else
			tmp = tmp->next;
	}
//	mostrar_tokens2(info);
	return (0);
}