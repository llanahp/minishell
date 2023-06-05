/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handles_cd_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:35:58 by mpizzolo          #+#    #+#             */
/*   Updated: 2023/06/04 23:29:42 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_cd_to_first_dir(t_inf *info)
{
	char	*to_location;
	char	*tmp;

	tmp = "/";
	to_location = info->pwd;
	if (!ft_strcmp(to_location, "/"))
		return (NULL);
	to_location = handle_back_cd(to_location);
	while (ft_strcmp(to_location, "/"))
	{
		free(to_location);
		to_location = handle_back_cd(to_location);
	}
	return (to_location);
}

int	check_user_cd(t_inf *info)
{
	if (!exist_var(info, "USER"))
	{
		ft_putstr_fd("minishell: cd: USER not set\n", 2);
		info->last_code = 1;
		return (0);
	}
	return (1);
}

void	cd_output_error(char *str)
{
	char	*tmp;

	ft_putstr_fd("minishell: cd: ", 2);
	if (str)
	{	
		tmp = ft_substr(str, 0, 2);
		if (!ft_strcmp(tmp, "./"))
		{
			str = ft_substr(str, 2, ft_strlen(str));
			free(str);
		}
		ft_putstr_fd(str, 2);
		free(tmp);
	}
	ft_putstr_fd("No such file or directory\n", 2);
}

char	*modify_str_for_change_env_cd(t_inf *info, char *arg)
{
	char	*to_location;
	char	*tmp;

	tmp = ft_substr(arg, 0, 2);
	if (!ft_strcmp(tmp, "./"))
		arg += 2;
	free(tmp);
	if (arg[ft_strlen(arg) - 1] == '/')
		arg[ft_strlen(arg) - 1] = '\0';
	if (ft_strcmp(info->pwd, "/"))
		to_location = ft_strjoin("/", arg);
	else
		to_location = ft_strdup(arg);
	return (to_location);
}
