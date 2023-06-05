/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:36:33 by ralopez-          #+#    #+#             */
/*   Updated: 2023/06/05 14:05:08 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*to_check_chdir(t_command *cmd, int *is_absolute)
{
	char	*to_location;
	char	*tmp;

	if (!ft_strcmp(cmd->args[0], "~"))
		return (ft_strdup("~"));
	tmp = ft_substr(cmd->args[0], 0, 2);
	to_location = NULL;
	if (!ft_strcmp(tmp, "./") || !ft_strcmp(tmp, "."))
		to_location = ft_strdup(cmd->args[0]);
	else if (!ft_strcmp(tmp, ".."))
	{
		if (cmd->args[0][ft_strlen(cmd->args[0]) - 1] == '/')
			cmd->args[0][ft_strlen(cmd->args[0]) - 1] = '\0';
		to_location = ft_strdup(cmd->args[0]);
	}
	else if (tmp[0] == '/')
	{	
		to_location = ft_strdup(cmd->args[0]);
		*is_absolute = 1;
	}
	else if (ft_strcmp(tmp, "./") && ft_isalnum(cmd->args[0][2] + 0))
		to_location = ft_strjoin("./", cmd->args[0]);
	else
		to_location = ft_strdup(cmd->args[0]);
	return (free(tmp), to_location);
}

char	*cd_handler(int abs, char *loc, t_command *cmd, t_inf *info)
{
	char	buf[PATH_MAX];

	if (!(cmd->args[0]) || !ft_strcmp(cmd->args[0], "")
		|| !ft_strcmp(cmd->args[0], "~") || !ft_strcmp(cmd->args[0], "--"))
		loc = handle_cd_to_home(info);
	else if (!ft_strcmp(cmd->args[0], "/"))
		loc = handle_cd_to_first_dir(info);
	else if (abs == 1)
		loc = ft_strdup(getcwd(buf, PATH_MAX));
	else if (!ft_strcmp(cmd->args[0], ".."))
		loc = handle_back_cd(info->pwd);
	else if (!ft_strcmp(cmd->args[0], "."))
		loc = ft_strdup(info->pwd);
	else if (!ft_strcmp(cmd->args[0], "-"))
		loc = handle_to_oldpwd(info, cmd);
	else
		loc = ft_strdup(getcwd(buf, PATH_MAX));
	if (loc == NULL)
		return (NULL);
	return (loc);
}

void	handling_cd(char *to_loc, t_command *cmd, t_inf *info, int is_abs)
{
	char	*tmp;

	tmp = to_loc;
	to_loc = cd_handler(is_abs, to_loc, cmd, info);
	free(tmp);
	if (to_loc == NULL)
		return ;
	if (exist_var(info, "OLDPWD") == 0 && info->pwd)
		add_var(info, "OLDPWD", info->pwd);
	else
		change_var_env(info, "OLDPWD", info->pwd);
	if (exist_var(info, "PWD") == 0 && to_loc)
		add_var(info, "PWD", to_loc);
	else
	{
		change_var_env(info, "PWD", to_loc);
	}
	free(to_loc);
}

char	*get_cd_location(t_inf *info, t_command *cmd, int *is_abs)
{
	char	*to_location;

	if (!cmd->args[0] || !ft_strcmp(cmd->args[0], ""))
		to_location = ft_strdup("~");
	else if (cmd->args[0][0] == '~' && ft_strcmp(cmd->args[0], "~"))
		to_location = expand_home_cd(cmd, info, is_abs);
	else
		to_location = to_check_chdir(cmd, is_abs);
	return (to_location);
}

int	cd(t_inf *info, t_command *cmd)
{
	char	*to_location;
	int		is_abs;
	int		chdir_exeption;

	is_abs = 0;
	get_pwd(info);
	if (info->env == NULL)
		return (0);
	to_location = get_cd_location(info, cmd, &is_abs);
	chdir_exeption = chdir_exeptions(to_location);
	if (chdir(to_location) == -1 && is_abs == 0 && chdir_exeption == 0)
	{
		cd_output_error(to_location);
		return (free(to_location), 127);
	}
	if (check_folder_exists() > 0)
		return (free(to_location), check_folder_exists_err());
	info->last_code = 0;
	handling_cd(to_location, cmd, info, is_abs);
	return (info->last_code);
}
