/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 13:02:30 by ralopez-          #+#    #+#             */
/*   Updated: 2023/06/03 13:02:31 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exist_var(t_inf *info, char *name)
{
	int	i;

	i = 0;
	if (name == NULL)
		return (0);
	if (info->env == NULL)
		return (0);
	while ((*info).env[i] != NULL && (*info).env[i][0] != '\0'
		&& ft_strncmp((*info).env[i], name, ft_strlen(name)) != 0)
		i++;
	if ((*info).env[i] == NULL
		|| ft_strncmp((*info).env[i], name, ft_strlen(name)) != 0)
		return (0);
	else
		return (1);
}

char	*get_var(t_inf *info, char *var)
{
	int	i;

	i = 0;
	if (var == NULL)
		return (NULL);
	if (info->env == NULL)
		return (NULL);
	while ((*info).env[i] != NULL && (*info).env[i][0] != '\0'
		&& ft_strncmp((*info).env[i], var, ft_strlen(var)) != 0)
		i++;
	if ((*info).env[i] == NULL
		|| ft_strncmp((*info).env[i], var, ft_strlen(var)) != 0)
		return (NULL);
	else
		return (ft_substr(info->env[i],
				ft_strlen(var) + 1, ft_strlen(info->env[i])));
}

void	copy_env(char **new, char **old)
{
	int	i;

	i = 0;
	if (old == NULL)
		return ;
	while (old && old[i])
	{
		new[i] = ft_strdup(old[i]);
		i++;
	}
	new[i] = NULL;
	new[i + 1] = NULL;
}

void	malloc_new_env(t_inf *info)
{
	char	**aux;
	int		i;

	i = 0;
	while (info->env && info->env[i])
		i++;
	aux = (char **)malloc(sizeof(char *) * (i + 2));
	if (!aux)
		return ;
	copy_env(aux, info->env);
	ft_free_split(info->env);
	info->env = NULL;
	info->env = aux;
}

void	add_var(t_inf *info, char *var, char *value)
{
	int		i;
	char	*str;
	char	*aux;
	char	*new;

	i = 0;
	aux = NULL;
	new = NULL;
	malloc_new_env(info);
	while (info->env[i] != NULL)
		i++;
	str = ft_strjoin(var, "=");
	if (value == NULL)
		new = ft_strdup(str);
	else
		new = ft_strjoin(str, value);
	info->env[i] = ft_strdup(new);
	if (str != NULL)
		free(str);
	if (new != NULL)
		free(new);
	i++;
	info->env[i] = NULL;
}
