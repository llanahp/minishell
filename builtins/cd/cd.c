/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:36:33 by ralopez-          #+#    #+#             */
/*   Updated: 2023/05/26 16:50:12 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*to_check_chdir(t_command *cmd, int *is_absolute)
{
	char	*to_location;
	char	*tmp;

	tmp = ft_substr(cmd->args[0], 0, 2);
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

int	chdir_exeptions(char *str)
{
	int	res;

	res = 0;
	if (ft_strcmp(str, "--"))
		res = 1;
	else if (ft_strcmp(str, "~"))
		res = 1;
	else if (ft_strcmp(str, "-"))
		res = 1;
	return (res);
}

// else if (ft_strcmp(tmp, "/") && ft_isalnum(cmd->args[0][0] + 0) && abs == 0)
// le saque ------------------- porque era la una que usaba tmp y tenia 5 args
char	*cd_handler(int abs, char *loc, t_command *cmd, t_inf *info)
{
	if (abs)
		loc = handle_absolute_path(loc);
	else if (!ft_strcmp(cmd->args[0], "..") || !ft_strcmp(loc, "-"))
		loc = handle_back_cd(info->pwd);
	else if (!ft_strcmp(cmd->args[0], "."))
		loc = info->pwd;
	else if (!ft_strcmp(cmd->args[0], "--") || !ft_strcmp(cmd->args[0], "~"))
		loc = handle_cd_to_usr(info);
	else
		loc = handle_cmd_for_change_env_cd(cmd->args[0], info->pwd);
	if (loc == NULL)
		return (NULL);
	return (loc);
}

int	cd(t_inf *info, t_command *cmd)
{
	char	*to_location;
	int		is_absolute;
	int		chdir_exeption;

	is_absolute = 0;
	get_pwd(info);
	if (!cmd->args[0])
	{
		to_location = "~";
		cmd->args[0] = "~";
	}
	else
		to_location = to_check_chdir(cmd, &is_absolute);
	chdir_exeption = chdir_exeptions(to_location);
	if (chdir(to_location) == -1 && is_absolute == 0 && chdir_exeption == 0)
		return (printf("chdir error\n"), 0);
	else
	{
		cd_handler(is_absolute, to_location, cmd, info);
		if (to_location == NULL)
			return (0);
		change_var_env(info, "OLDPWD", info->pwd);
		change_var_env(info, "PWD", to_location);
	}
	return (0);
}
