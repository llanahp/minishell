/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:36:33 by ralopez-          #+#    #+#             */
/*   Updated: 2023/05/26 15:48:44 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*to_check_chdir(t_command *cmd, char *tmp, int *is_absolute)
{
	char	*to_location;

	to_location = NULL;
	if (!ft_strcmp(tmp, "./") || !ft_strcmp(tmp, "..")
		|| !ft_strcmp(tmp, "."))
		to_location = cmd->args[0];
	else if (tmp[0] == '/')
	{	
		to_location = cmd->args[0];
		*is_absolute = 1;
	}
	else if (ft_strcmp(tmp, "./") && ft_isalnum(cmd->args[0][2] + 0))
		to_location = ft_strjoin("./", cmd->args[0]);
	else
		to_location = cmd->args[0];
	return (to_location);
}

char	*handle_back_cd(char *pwd)
{
	char	*to_location;
	char	*tmp;

	to_location = pwd;
	tmp = ft_strrchr(to_location, '/');
	*tmp = '\0';
	return (to_location);
}

char	*handle_cmd_for_change_env_cd(char *arg, char *pwd)
{
	char	*to_location;

	to_location = ft_strjoin("/", arg);
	to_location = ft_strjoin(pwd, to_location);
	return (to_location);
}

char	*handle_cd_to_usr(t_inf *info)
{
	char	*to_location;
	char	*usr;
	char	*tmp;

	usr = ft_strjoin("/", get_var(info, "USER"));
	to_location = handle_back_cd(info->pwd);
	if (chdir(to_location) == -1)
		return (printf("chdir error\n"), NULL);
	tmp = ft_strrchr(to_location, '/');
	while (ft_strcmp(tmp, usr)){
		to_location = handle_back_cd(info->pwd);
		if (chdir(to_location) == -1)
			return (printf("chdir error\n"), NULL);
		tmp = ft_strrchr(to_location, '/');
	}
	return (to_location);
}

int	ft_strichr(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (i);
	}
	return (-1);
}

char *ft_get_first_directory(char *path)
{
	char	*first_sep;
	size_t	len;
	char	*first_dir;
	
	first_sep = ft_strchr(path, '/');
	if (first_sep == NULL)
		return NULL;
	if (first_sep == path)
		return (path);
	len = (size_t)(first_sep - path);
	first_dir = ft_substr(path, 0, len);
	return first_dir;
}

char	*handle_absolute_path(t_inf *info, char *absolute_path)
{
	char	*to;
	char	*to_loc;
	char	*tmp;
	int		i_tmp;

	to = absolute_path;
	to_loc = "";
	i_tmp = ft_strichr(to + 1, '/');
	if (i_tmp == -1)
		tmp = ft_substr(to, 0, ft_strlen(to));
	else
		tmp = ft_substr(to, 0, i_tmp + 1);
	to = ft_strchr(to + 1, '/');
	to_loc = ft_strjoin(to_loc, tmp);
	if (chdir(to_loc) == -1)
			return (printf("chdir error, d: %s\n", to_loc), NULL);
	while (ft_strcmp(tmp, absolute_path) && i_tmp != -1 && to)
	{
		i_tmp = ft_strichr(to + 1, '/');
		if (i_tmp == -1)
			tmp = ft_substr(to, 0, ft_strlen(to));
		else
			tmp = ft_substr(to, 0, i_tmp + 1);
		to = ft_strchr(to + 1, '/');
		to_loc = ft_strjoin(to_loc, tmp);
		if (chdir(to_loc) == -1)
				return (printf("chdir error, d: %s\n", to_loc), NULL);
	}
	if (to_loc[ft_strlen(to_loc) - 1] == '/')
		to_loc = ft_substr(to_loc, 0, ft_strlen(to_loc) - 1);
	return (to_loc);
}

int	chdir_exeptions(char *str)
{
	int res;
	
	res = 0;
	if (ft_strcmp(str, "--"))
		res = 1;
	else if (ft_strcmp(str, "~"))
		res = 1;
	else if (ft_strcmp(str, "-"))
		res = 1;
	return (res);
}

int	cd(t_inf *info, t_command *cmd)
{
	char	*to_location;
	char	*tmp;
	int		is_absolute;
	int		chdir_exeption;

	is_absolute = 0;
	get_pwd(info);
	if(!cmd->args[0])
	{
		to_location = "~";
		cmd->args[0] = "~";
	}
	else
	{
		tmp = ft_substr(cmd->args[0], 0, 2);
		to_location = to_check_chdir(cmd, tmp, &is_absolute);
	}
	chdir_exeption = chdir_exeptions(to_location);
	if (chdir(to_location) == -1 && is_absolute == 0 && chdir_exeption == 0)
		return(printf("chdir error\n"), 0);
	else
	{
		if (is_absolute)
			to_location = handle_absolute_path(info, to_location);
		else if (ft_strcmp(tmp, "/") && ft_isalnum(cmd->args[0][0] + 0) && is_absolute == 0)
			to_location = handle_cmd_for_change_env_cd(cmd->args[0], info->pwd);
		else if (!ft_strcmp(cmd->args[0], "..") || !ft_strcmp(to_location, "-"))
			to_location = handle_back_cd(info->pwd);
		else if (!ft_strcmp(cmd->args[0], "."))
			to_location = info->pwd;
		else if (!ft_strcmp(cmd->args[0], "--") || !ft_strcmp(cmd->args[0], "~"))
			to_location = handle_cd_to_usr(info);
		if (to_location == NULL)
			return (0);
		change_var_env(info, "OLDPWD", info->pwd);
		change_var_env(info, "PWD", to_location);
	}
	return (0);
}
