/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:36:33 by ralopez-          #+#    #+#             */
/*   Updated: 2023/05/20 18:46:55 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*to_check_chdir(t_command *cmd, char *tmp)
{
	char	*to_location;

	to_location = NULL;
	if (ft_strcmp(tmp, "./") && ft_isalnum(cmd->args[0][2] + 0))
		to_location = ft_strjoin("./", cmd->args[0]);
	else if (!ft_strcmp(tmp, "./") || !ft_strcmp(tmp, "..")
		|| !ft_strcmp(tmp, "."))
		to_location = cmd->args[0];
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
	tmp = ft_strrchr(to_location, '/');
	while (ft_strcmp(tmp, usr)){
		to_location = handle_back_cd(info->pwd);
		tmp = ft_strrchr(to_location, '/');
	}
	return (to_location);
}

int	cd(t_inf *info, t_command *cmd)
{
	char	*to_location;
	char	*tmp;

	get_pwd(info);
	tmp = ft_substr(cmd->args[0], 0, 2);
	to_location = to_check_chdir(cmd, tmp);
	if (chdir(to_location) == -1 && ft_strcmp(to_location, "--") && ft_strcmp(to_location, "~"))
		printf("chdir error\n");
	else
	{
		if (ft_strcmp(tmp, "/") && ft_isalnum(cmd->args[0][0] + 0))
			to_location = handle_cmd_for_change_env_cd(cmd->args[0], info->pwd);
		else if (!ft_strcmp(cmd->args[0], ".."))
			to_location = handle_back_cd(info->pwd);
		else if (!ft_strcmp(cmd->args[0], "."))
			to_location = info->pwd;
		else if (!ft_strcmp(cmd->args[0], "--") || !ft_strcmp(cmd->args[0], "~"))
			to_location = handle_cd_to_usr(info);
		change_var_env(info, "OLDPWD", info->pwd);
		change_var_env(info, "PWD", to_location);
	}
	return (0);
}
