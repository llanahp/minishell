/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:41:20 by ralopez-          #+#    #+#             */
/*   Updated: 2023/03/10 10:41:21 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int	ft_find(char *line, char character)
{
	int	i;
	int position;

	i = 0;
	position = -1;
	while (line[i] && line[i] != character)
		i++;
	if (line[i] == character)
		position = i;
	return (position);
}

int	export_binding(t_inf *info, char *line)
{
	char	*name;
	char	*value;
	int		equals;

	equals = ft_find(line, '=');
	name = ft_substr(line, 7, equals - 7);
	value = ft_substr(line, equals + 1, ft_strlen(line));
	if (get_var(info, name) == NULL)
		add_var(info, name, value);
	else
		change_var_env(info, name, value);
	return (0);
}