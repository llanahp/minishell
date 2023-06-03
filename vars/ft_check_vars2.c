/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_vars2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 15:43:10 by ralopez-          #+#    #+#             */
/*   Updated: 2023/05/27 15:43:11 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	copy_value(char *value, char *new, int *j)
{
	int	h;

	h = 0;
	while (value[h])
		new[(*j)++] = value[h++];
}

void	replace_for_var_aux(char **new, char **str, char *value, int index)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while ((*str)[i])
	{
		k = 0;
		if ((*str)[i] == '$' && i == index)
		{
			if ((*str)[i] == '$' && (*str)[i + 1] == '$')
				k = 1;
			copy_value(value, (*new), &j);
			i = i + len_var((*str) + index) + 1 + k;
			if ((*str)[i] == '\0')
				break ;
		}
		(*new)[j++] = (*str)[i++];
	}
	(*new)[j] = '\0';
}

void	replace_for_var(char **str, char *value, int index)
{
	char	*new;

	new = (char *)malloc(sizeof(char)
			* (ft_strlen(*str) + ft_strlen(value) + 2));
	if (!new)
		return ;
	replace_for_var_aux(&new, str, value, index);
	free((*str));
	(*str) = new;
}

void	replace_for_null(char **str, int index)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = (char *)malloc(sizeof(char) * (ft_strlen((*str) + 1)) + 1);
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

int	replace_var(char **str, int i, t_inf *info)
{
	char	*var;
	char	*value;

	var = get_name(*str + i);
	if (var == NULL)
		return (-1);
	value = get_var(info, var);
	if (value != NULL)
		replace_for_var(str, value, i);
	else
		replace_for_null(str, i);
	if (var != NULL)
		free(var);
	if (value != NULL)
		free(value);
	return (0);
}
