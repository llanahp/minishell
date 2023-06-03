/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handles_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:57:41 by mpizzolo          #+#    #+#             */
/*   Updated: 2023/06/03 23:08:40 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handling_cd(char *to_location, t_command *cmd, t_inf *info, int is_abs)
{
	char	*tmp;

	tmp = to_location;
	to_location = cd_handler(is_abs, to_location, cmd, info);
	free(tmp);
	if (to_location == NULL)
		return ;
	if (exist_var(info, "OLDPWD") == 0 && info->pwd)
		add_var(info, "OLDPWD", info->pwd);
	else
		change_var_env(info, "OLDPWD", info->pwd);
	if (exist_var(info, "PWD") == 0 && to_location)
		add_var(info, "PWD", to_location);
	else
		change_var_env(info, "PWD", to_location);
	free(to_location);
}

char	*handle_cmd_for_change_env_cd(t_inf *info, char *arg, char *pwd)
{
	char	*to_location;
	char	*tmp;

	to_location = NULL;
	tmp = NULL;
	to_location = modify_str_for_change_env_cd(info, arg);
	tmp = to_location;
	to_location = ft_strjoin(pwd, to_location);
	free(tmp);
	if (chdir(to_location) == -1)
	{
		info->last_code = 127;
		tmp = to_location;
		to_location = ft_strrchr(to_location, '/') + 1;
		cd_output_error(to_location);
		free(tmp);
		return (NULL);
	}
	return (to_location);
}

char	*handle_for_absolute(char **to, char *to_loc)
{
	char	*res;
	char	*tmp;
	int		i_tmp;

	i_tmp = ft_strichr(to[0] + 1, '/');
	if (i_tmp != -1)
		tmp = ft_substr(to[0], 0, ft_strlen(to[0]));
	else
		tmp = ft_substr(to[0], 0, i_tmp + 1);
	to[0] = ft_strchr(to[0] + 1, '/');
	res = ft_strjoin(to_loc, tmp);
	free(tmp);
	return (res);
}

char	*handle_absolute_path(t_inf *info, char *absolute_path)
{
	char	*to;
	char	*to_loc;
	char	*tmp;
	char	*tmp_free;

	to = absolute_path;
	to_loc = handle_for_absolute(&to, "");
	if (chdir(to_loc) == -1)
	{
		info->last_code = 127;
		return (handle_chdir_error(to_loc, NULL), NULL);
	}
	while (ft_strcmp(to_loc, absolute_path) && to)
	{
		tmp = to_loc;
		free(to);
		to_loc = handle_for_absolute(&to, to_loc);
		free(tmp);
		if (chdir(to_loc) == -1)
		{
			info->last_code = 127;
			printf("holis\n");
			return (handle_chdir_error(to_loc, to), NULL);
		}
	}
	if (to_loc[ft_strlen(to_loc) - 1] == '/')
		to_loc[ft_strlen(to_loc) - 1] = '\0';
	printf("2---------\n");
	system("leaks -q minishell");
	return (free(to), to_loc);
}
