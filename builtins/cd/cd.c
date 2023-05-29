/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:36:33 by ralopez-          #+#    #+#             */
/*   Updated: 2023/05/29 18:54:44 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*to_check_chdir(t_command *cmd, int *is_absolute)
{
	char	*to_location;
	char	*tmp;

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
	free(tmp);
	return (to_location);
}

int	chdir_exeptions(char *str)
{
	int	res;

	res = 0;
	if (!ft_strcmp(str, "--"))
		res = 1;
	else if (!ft_strcmp(str, "~"))
		res = 1;
	else if (!ft_strcmp(str, "-"))
		res = 1;
	return (res);
}

char	*cd_handler(int abs, char *loc, t_command *cmd, t_inf *info)
{
	if (abs == 1)
		loc = handle_absolute_path(loc);
	else if (!ft_strcmp(cmd->args[0], "..") || !ft_strcmp(loc, "-"))
		loc = handle_back_cd(info->pwd);
	else if (!ft_strcmp(cmd->args[0], "."))
		loc = ft_strdup(info->pwd);
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
	int		is_abs;
	int		chdir_exeption;

	is_abs = 0;
	get_pwd(info);
	if (!cmd->args[0])
		handle_no_arg_cd(cmd, &to_location);
	else
		to_location = to_check_chdir(cmd, &is_abs);
	chdir_exeption = chdir_exeptions(to_location);
	if (chdir(to_location) == -1 && is_abs == 0 && chdir_exeption == 0)
	{
		printf("cd: no such file or directory: %s\n", to_location);
		free(to_location);
		return (0);
	}
	else
		handling_cd(to_location, cmd, info, is_abs);
	system("leaks -q minishell");
	return (0);
}
