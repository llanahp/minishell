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

char	*get_value_var_line(char *name, char *line)
{
	char	*value;

	value = NULL;
	if (name == NULL || line == NULL)
		return (NULL);
	value = ft_substr(line, ft_strlen(name) + 1, ft_strlen(line));
	if (value != NULL && value[0] == '\0')
	{
		free(value);
		value = NULL;
	}
	return (value);
}

int	export_binding(t_inf *info, t_command *cmd)
{
	char	*name;
	char	*value;
	int 	i;

	i = 0;
	if (cmd->args[0] == NULL)
			return (env_export(info));
	while (cmd->args!= NULL && cmd->args[i] != NULL)
	{
		name = get_name_var_line(cmd->args[i]);
		value = get_value_var_line(name, cmd->args[i]);
		if (name == NULL || ft_isdigit(name[0]) == 1 || ft_strcontains(name, '+') == 1)
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(cmd->args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			if (name)
				free(name);
			if (value)
				free(value);
			return (1);
		}
		else if(value == NULL)
		{
			printf("HO hago nada\n");
		}
		else if (exist_var(info, name) == 1)
		{
			if (value != NULL)
				change_var_env(info, name, value);
			else if (value == NULL && ft_strcontains(cmd->args[i], '=') == 1)
				change_var_env(info, name, value);
		}
		else
			add_var(info, name, value);
		if (name)
			free(name);
		if (value)
			free(value);
			
		i++;
	}
	return (0);
}
