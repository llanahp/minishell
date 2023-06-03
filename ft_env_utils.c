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

void	store_env(t_inf *info, char **env)
{
	int	i;
	int	j;

	i = 0;
	if (env[0] == NULL)
	{
		store_when_env_null(info);
		return ;
	}
	while (env[i])
		i++;
	j = i - 1;
	info->env = (char **)malloc(sizeof(char *) * (j + 1));
	if (! info->env)
		return ;
	i = 0;
	j = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "OLDPWD=", 7))
		{
			info->env[j] = ft_strdup(env[i]);
			j++;
		}
		i++;
	}
	info->env[j] = NULL;
}

/** get_enviroment:
 * This function is called after verify that enviroment exist
 * Iterates all enviroment string to since find the string "PATH=" 
 * or reach the end
 * 
 * Returns 1 if string "PATH=" is find and store the rest of the string 
 * in info.paths splited by character ':'.
 * 
 * Returns -1 enviroment dosen´t containst "PATH=".
 */
int	get_enviroment(t_inf *info, char **env)
{
	int		i;
	char	*temp;

	i = 0;
	store_env(info, env);
	if (info->env == NULL)
		return (-1);
	while (info->env[i] != NULL && info->env[i][0] != '\0'
		&& ft_strncmp(info->env[i], "PATH=", 5) != 0)
		i++;
	if (info->env != NULL && (info->env[i] == NULL || ft_strncmp(info->env[i], "PATH=", 5)) != 0)
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
	while (info->env[i] != NULL && ft_strncmp(info->env[i], name, ft_strlen(name)) != 0)
		i++;
	if (info->env[i] == NULL || ft_strncmp(info->env[i], name, ft_strlen(name)) != 0)
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
	if ((*info).env[i] == NULL || ft_strncmp((*info).env[i], name, ft_strlen(name)) != 0)
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
	if ((*info).env[i] == NULL || ft_strncmp((*info).env[i], var, ft_strlen(var)) != 0)
		return (NULL);
	else
		return (ft_substr((*info).env[i], ft_strlen(var) + 1, ft_strlen((*info).env[i])));
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
	char 	*aux;
	char	*new;

	i = 0;
	aux= NULL;
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
