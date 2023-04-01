/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:33:40 by ralopez-          #+#    #+#             */
/*   Updated: 2023/03/10 13:33:41 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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
int	get_enviroment(t_inf *info)
{
	int		i;
	char	*temp;

	i = 0;
	while ((*info).env[i] != NULL && (*info).env[i][0] != '\0'
		&& ft_strncmp((*info).env[i], "PATH=", 5) != 0)
		i++;
	if (ft_strncmp((*info).env[i], "PATH=", 5) != 0)
		return (-1);
	else
	{
		temp = ft_substr((*info).env[i], 5, ft_strlen((*info).env[i]));
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
	while ((*info).env[i] != NULL && (*info).env[i][0] != '\0'
		&& ft_strncmp((*info).env[i], "PWD=", 4) != 0)
		i++;
	if (ft_strncmp((*info).env[i], "PWD=", 4) != 0)
		return (1);
	else
	{
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
	while ((*info).env[i] != NULL && (*info).env[i][0] != '\0'
		&& ft_strncmp((*info).env[i], name, ft_strlen(name)) != 0)
		i++;
	
	if (info->env[i] == NULL || ft_strncmp((*info).env[i], name, ft_strlen(name)) != 0)
	{
		free(name);
		return (1);
	}
	while ((*info).env[i])
	{
		(*info).env[i] = (*info).env[i + 1];
		i++;
	}
	free(name);
	return (0);
}

void	change_var_env(t_inf *info, char *var, char *value)
{
	int		i;
	char	*str;

	i = 0;
	while ((*info).env[i] != NULL && (*info).env[i][0] != '\0'
		&& ft_strncmp((*info).env[i], var, ft_strlen(var)) != 0)
		i++;
	if (ft_strncmp((*info).env[i], var, ft_strlen(var)) != 0)
		return ;
	str = ft_strjoin(var, "=");
	(*info).env[i] = ft_strjoin(str, value);
}

char	*get_var(t_inf *info, char *var)
{
	int		i;

	i = 0;
	while ((*info).env[i] != NULL && (*info).env[i][0] != '\0'
		&& ft_strncmp((*info).env[i], var, ft_strlen(var)) != 0)
		i++;
	if ((*info).env[i] == NULL || ft_strncmp((*info).env[i], var, ft_strlen(var)) != 0)
		return (NULL);
	else
		return (ft_substr((*info).env[i], ft_strlen(var) + 1, ft_strlen((*info).env[i])));
}

void	add_var(t_inf *info, char *var, char *value)
{
	int		i;
	char	*str;

	i = 0;
	while ((*info).env[i] != NULL && (*info).env[i][0] != '\0')
		i++;
	str = ft_strjoin(var, "=");
	(*info).env[i] = ft_strjoin(str, value);
	free(str);
	i++;
	(*info).env[i] = NULL;
}