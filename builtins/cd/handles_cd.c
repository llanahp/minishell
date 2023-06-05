/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handles_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:57:41 by mpizzolo          #+#    #+#             */
/*   Updated: 2023/06/05 13:58:31 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_home_cd(t_command *cmd, t_inf *info, int *is_abs)
{
	char	*home;
	char	*res;
	char	*str;

	str = cmd->args[0];
	home = get_var(info, "HOME");
	str = ft_substr(str, 1, ft_strlen(str));
	res = ft_strjoin(home, str);
	free(home);
	free(str);
	str = cmd->args[0];
	cmd->args[0] = res;
	free(str);
	*is_abs = 1;
	return (ft_strdup(res));
}

int	check_back_before_cd(char *str)
{
	int		args;

	args = 0;
	if (str[0] == '.' && str[1] == '.' && str[2] == '/'
		&& ft_isalnum(str[3]) + 0)
		args++;
	return (args);
}

void	changing_pwd_oldpwd(t_inf *info, char *to)
{
	if (exist_var(info, "OLDPWD") == 0 && info->pwd)
		add_var(info, "OLDPWD", info->pwd);
	else
		change_var_env(info, "OLDPWD", info->pwd);
	if (exist_var(info, "PWD") == 0 && to)
		add_var(info, "PWD", to);
	else
		change_var_env(info, "PWD", to);
}

void	manage_back_and_cd(t_command *cmd, t_inf *info, int *exep)
{
	char	*str;
	char	*to;

	str = cmd->args[0];
	if (chdir(str) == -1)
	{
		if (!check_back_before_cd(str))
			return ;
		cd_output_error(str);
		return ;
	}
	chdir(info->pwd);
	if (!check_back_before_cd(str))
		return ;
	if (chdir("..") == -1)
		printf("erro");
	to = handle_back_cd(info->pwd);
	changing_pwd_oldpwd(info, to);
	free(to);
	cmd->args[0] = ft_substr(str, 3, ft_strlen(str));
	free(str);
	*exep = 1;
	get_pwd(info);
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
