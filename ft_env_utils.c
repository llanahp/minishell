/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:33:40 by ralopez-          #+#    #+#             */
/*   Updated: 2023/06/03 13:51:21 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	store_when_env_null(t_inf *info)
{
	info->env = (char **)malloc(sizeof(char *) * (3));
	info->env[0] = ft_strjoin("PWD=", getcwd(info->pwd, 100));
	info->env[1] = ft_strdup("SHLVL=1");
	info->env[2] = ft_strdup("_=");
}

int	store_paths(t_inf *info)
{
	int		i;
	char	*temp;

	i = 0;
	info->paths = NULL;
	if (info->env == NULL)
		return (-1);
	while (info->env[i] != NULL && info->env[i][0] != '\0'
		&& ft_strncmp(info->env[i], "PATH=", 5) != 0)
		i++;
	if (info->env != NULL
		&& (info->env[i] == NULL || ft_strncmp(info->env[i], "PATH=", 5)) != 0)
		return (-1);
	else
	{
		temp = ft_substr(info->env[i], 5, ft_strlen(info->env[i]));
		info->paths = ft_split(temp, ':');
		free(temp);
		return (1);
	}
}

int	get_pwd(t_inf *info)
{
	int		i;

	i = 0;
	if (info->pwd != NULL)
	{
		free(info->pwd);
		info->pwd = NULL;
	}
	if (info->env == NULL)
		return (1);
	while ((*info).env[i] != NULL && (*info).env[i][0] != '\0'
		&& ft_strncmp((*info).env[i], "PWD=", 4) != 0)
		i++;
	if ((*info).env[i] != NULL && ft_strncmp((*info).env[i], "PWD=", 4) != 0)
		return (1);
	else
	{
		if ((*info).env[i] == NULL)
			info->pwd = getcwd(info->pwd, 100);
		else
			info->pwd = ft_substr((*info).env[i], 4, ft_strlen((*info).env[i]));
		return (0);
	}
}

int	delete_var(t_inf *info, char *var)
{
	int		i;
	char	*name;

	i = 0;
	name = ft_strjoin(var, "=");
	while (info->env[i] != NULL
		&& ft_strncmp(info->env[i], name, ft_strlen(name)) != 0)
		i++;
	if (info->env[i] == NULL
		|| ft_strncmp(info->env[i], name, ft_strlen(name)) != 0)
	{
		free(name);
		return (0);
	}
	else
		free(info->env[i]);
	while (info->env[i])
	{
		info->env[i] = info->env[i + 1];
		i++;
	}
	free(name);
	return (0);
}

void	change_var_env(t_inf *info, char *var, char *value)
{
	int		i;
	char	*str;
	char	*new;

	i = 0;
	while ((*info).env[i] != NULL && (*info).env[i][0] != '\0'
		&& ft_strncmp((*info).env[i], var, ft_strlen(var)) != 0)
		i++;
	if (ft_strncmp((*info).env[i], var, ft_strlen(var)) != 0)
		return ;
	str = ft_strjoin(var, "=");
	free(info->env[i]);
	if (value == NULL)
		new = ft_strdup(str);
	else
		new = ft_strjoin(str, value);
	free(str);
	info->env[i] = ft_strdup(new);
	free(new);
}
