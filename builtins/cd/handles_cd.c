/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handles_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:57:41 by mpizzolo          #+#    #+#             */
/*   Updated: 2023/05/29 21:13:42 by mpizzolo         ###   ########.fr       */
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
	change_var_env(info, "OLDPWD", info->pwd);
	change_var_env(info, "PWD", to_location);
	free(to_location);
}

char	*handle_cmd_for_change_env_cd(char *arg, char *pwd)
{
	char	*to_location;
	char	*tmp;

	to_location = NULL;
	tmp = NULL;
	tmp = ft_substr(arg, 0, 2);
	if (!ft_strcmp(tmp, "./"))
		arg += 2;
	free(tmp);
	if (arg[ft_strlen(arg) - 1] == '/')
		arg[ft_strlen(arg) - 1] = '\0';
	to_location = ft_strjoin("/", arg);
	tmp = to_location;
	to_location = ft_strjoin(pwd, to_location);
	free(tmp);
	if (chdir(to_location) == -1)
	{
		tmp = to_location;
		to_location = ft_strrchr(to_location, '/') + 1;
		printf("cd: no such file or directory: %s\n", to_location);
		free(tmp);
		return (NULL);
	}
	return (to_location);
}

char	*handle_cd_to_usr(t_inf *info)
{
	char	*to_location;
	char	*usr;
	char	*tmp;
	char	*tmp_free;

	tmp = get_var(info, "USER");
	usr = ft_strjoin("/", tmp);
	free(tmp);
	if (check_on_root(info) == 1)
		return (free(usr), NULL);
	to_location = handle_back_cd(info->pwd);
	if (chdir(to_location) == -1)
		return (handle_chdir_error(to_location, usr), NULL);
	tmp = ft_strrchr(to_location, '/');
	while (ft_strcmp(tmp, usr))
	{
		tmp_free = to_location;
		to_location = handle_back_cd(to_location);
		free(tmp_free);
		if (chdir(to_location) == -1)
			return (handle_chdir_error(to_location, usr), NULL);
		tmp = ft_strrchr(to_location, '/');
	}
	free(usr);
	return (to_location);
}

char	*handle_for_absolute(char **to, char *to_loc)
{
	char	*res;
	char	*tmp;
	int		i_tmp;

	i_tmp = ft_strichr(to[0] + 1, '/');
	if (i_tmp == -1)
		tmp = ft_substr(to[0], 0, ft_strlen(to[0]));
	else
		tmp = ft_substr(to[0], 0, i_tmp + 1);
	to[0] = ft_strchr(to[0] + 1, '/');
	res = ft_strjoin(to_loc, tmp);
	free(tmp);
	return (res);
}

char	*handle_absolute_path(char *absolute_path)
{
	char	*to;
	char	*to_loc;
	char	*tmp;

	to = absolute_path;
	to_loc = handle_for_absolute(&to, "");
	if (chdir(to_loc) == -1)
		return (handle_chdir_error(to_loc, NULL), NULL);
	while (ft_strcmp(to_loc, absolute_path) && to)
	{
		tmp = to_loc;
		to_loc = handle_for_absolute(&to, to_loc);
		free(tmp);
		if (chdir(to_loc) == -1)
			return (handle_chdir_error(to_loc, NULL), NULL);
	}
	if (to_loc[ft_strlen(to_loc) - 1] == '/')
		to_loc[ft_strlen(to_loc) - 1] = '\0';
	free(to);
	return (to_loc);
}
