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

char	*to_check_chdir(t_command *cmd, char *tmp, int *is_absolute)
{
	char	*to_location;

	to_location = NULL;
	if (!ft_strcmp(tmp, "./") || !ft_strcmp(tmp, "..")
		|| !ft_strcmp(tmp, "."))
		to_location = cmd->args[0];
	else if (tmp[0] == '/')
	{	
		to_location = ft_strjoin(".", cmd->args[0]);
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

// hacer primero handle_cd_to_usr() y desde ahi al absolute??
char	*handle_absolute_path(t_inf *info, char *absolute_path)
{
	// char	*to_location;
	// char	*to;
	// char	*tmp;

	//TEMPORAL
	if (1 == 2)
		info = NULL;
	if (1 == 2)
		absolute_path = NULL;
	printf("Absolute path\n");
	// to = absolute_path;
	// to_location = handle_back_cd(info->pwd);
	// if (chdir(to_location) == -1)
	// 	return (printf("chdir error\n"), NULL);
	// tmp = ft_strrchr(to_location, '/');
	// while (ft_strcmp(tmp, to)){
	// 	to_location = handle_back_cd(info->pwd);
	// 	if (chdir(to_location) == -1)
	// 		return (printf("chdir error\n"), NULL);
	// 	tmp = ft_strrchr(to_location, '/');
	// }
	return (NULL);
}

int	cd(t_inf *info, t_command *cmd)
{
	char	*to_location;
	char	*tmp;
	int		is_absolute;

	is_absolute = 0;
	get_pwd(info);
	tmp = ft_substr(cmd->args[0], 0, 2);
	to_location = to_check_chdir(cmd, tmp, &is_absolute);
	if (chdir(to_location) == -1 && ft_strcmp(to_location, "--") && ft_strcmp(to_location, "~") && ft_strcmp(to_location, "-") && is_absolute == 0)
		return(printf("chdir error\n"), 0);
	else
	{
		// handle absolute path
		if (ft_strcmp(tmp, "/") && ft_isalnum(cmd->args[0][0] + 0) && !is_absolute)
			to_location = handle_cmd_for_change_env_cd(cmd->args[0], info->pwd);
		else if (!ft_strcmp(cmd->args[0], "..") || !ft_strcmp(to_location, "-"))
			to_location = handle_back_cd(info->pwd);
		else if (!ft_strcmp(cmd->args[0], "."))
			to_location = info->pwd;
		else if (!ft_strcmp(cmd->args[0], "--") || !ft_strcmp(cmd->args[0], "~"))
			to_location = handle_cd_to_usr(info);
		if (is_absolute)
			to_location = handle_absolute_path(info, to_location);
		if (to_location == NULL)
			return (0);
		change_var_env(info, "OLDPWD", info->pwd);
		change_var_env(info, "PWD", to_location);
	}
	return (0);
}
