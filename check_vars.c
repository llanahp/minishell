/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:08:25 by ralopez-          #+#    #+#             */
/*   Updated: 2023/03/31 14:08:27 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void mostrar_tokens2(t_inf *info)
{
	printf("--------------\n");
	while (info->tokens)
	{
		printf("%s\n", (char *)info->tokens->content);
		info->tokens = info->tokens->next;
	}
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
	while (line[j] && line[j] != ' ' && line[j] != '\t' && line[j] != '$')
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

int	check_vars(t_inf *info)
{
	t_list	*tmp;
	char	*var;
	char	 *name;

	tmp = info->tokens;
	while (tmp)
	{
		if (ft_strcontains(tmp->content, '$'))
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
		else
			tmp = tmp->next;
	}
	mostrar_tokens2(info);
	return (0);
}