/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 16:07:42 by mpizzolo          #+#    #+#             */
/*   Updated: 2023/06/03 16:15:51 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	do_export(t_inf *info, char *str, char *name, char *value)
{
	if (exist_var(info, name) == 1)
	{
		if (value != NULL)
			change_var_env(info, name, value);
		else if (value == NULL && ft_strcontains(str, '=') == 1)
			change_var_env(info, name, value);
	}
	else
		add_var(info, name, value);
}

int	ft_n_aparitions(char *str, char c)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			n++;
		i++;
	}
	return (n);
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

void	export_binding_err(char *name, char *value, t_command *cmd, int i)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(cmd->args[i], 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	if (name)
		free(name);
	if (value)
		free(value);
}
