/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:41:20 by ralopez-          #+#    #+#             */
/*   Updated: 2023/05/20 18:17:47 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_find(char *line, char character)
{
	int	i;
	int	position;

	i = 0;
	position = -1;
	while (line[i] && line[i] != character)
		i++;
	if (line[i] == character)
		position = i;
	return (position);
}

int	export_binding(t_inf *info, t_command *cmd)
{
	char	*name;
	char	*value;
	int		equals;

	equals = ft_find(cmd->args[0], '=');
	name = ft_substr(cmd->args[0], 0, equals);
	equals++;
	value = ft_substr(cmd->args[0], equals, (ft_strlen(cmd->args[0]) - equals));
	if (get_var(info, name) == NULL)
		add_var(info, name, value);
	else
		change_var_env(info, name, value);
	return (0);
}
