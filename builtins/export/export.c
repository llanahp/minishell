/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:41:20 by ralopez-          #+#    #+#             */
/*   Updated: 2023/06/03 16:15:55 by mpizzolo         ###   ########.fr       */
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

char	*get_name_var_line(char *line)
{
	int		equals;
	char	*name;

	if (line == NULL)
		return (NULL);
	if (ft_strcontains(line, '=') == 0)
		name = ft_strdup(line);
	else
	{
		equals = ft_find(line, '=');
		name = ft_substr(line, 0, equals);
	}
	if (name != NULL && name[0] == '\0')
	{
		free(name);
		name = NULL;
	}
	return (name);
}

int	name_export_invalid(char *name)
{
	int	len;

	if (name == NULL || name[0] == '\0')
		return (1);
	if (ft_strcontains(name, '=') == 1 || ft_strcontains(name, '~') == 1
		|| ft_strcontains(name, '!') == 1 || ft_strcontains(name, '$') == 1
		|| ft_strcontains(name, '@') == 1 || ft_strcontains(name, '#') == 1
		|| ft_strcontains(name, '{') == 1 || ft_strcontains(name, '}') == 1
		|| ft_strcontains(name, '-') == 1 || ft_strcontains(name, '.') == 1
		|| ft_strcontains(name, '^') == 1 || ft_strcontains(name, '*') == 1)
		return (1);
	len = ft_strlen(name);
	if (ft_n_aparitions(name, '+') > 1 || (ft_strcontains(name, '+') == 1
			&& len > 1 && name[len - 1] != '+'))
		return (1);
	return (0);
}

int	export_binding(t_inf *info, t_command *cmd)
{
	char	*name;
	char	*value;
	int		i;

	i = 0;
	if (cmd->args[0] == NULL)
		return (env_export(info));
	while (cmd->args != NULL && cmd->args[i] != NULL)
	{
		name = get_name_var_line(cmd->args[i]);
		value = get_value_var_line(name, cmd->args[i]);
		if (name == NULL || name_export_invalid(name) == 1
			|| ft_isdigit(name[0]) == 1)
			return (export_binding_err(name, value, cmd, i), 1);
		else
			do_export(info, cmd->args[i], name, value);
		if (name)
			free(name);
		if (value)
			free(value);
		i++;
	}
	return (0);
}
