/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handles_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:57:41 by mpizzolo          #+#    #+#             */
/*   Updated: 2023/05/26 16:58:06 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	while (ft_strcmp(tmp, usr))
	{
		to_location = handle_back_cd(info->pwd);
		if (chdir(to_location) == -1)
			return (printf("chdir error\n"), NULL);
		tmp = ft_strrchr(to_location, '/');
	}
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
	// free(to_loc);
	return (res);
}

char	*handle_absolute_path(char *absolute_path)
{
	char	*to;
	char	*to_loc;

	to = absolute_path;
	to_loc = "";
	to_loc = handle_for_absolute(&to, to_loc);
	if (chdir(to_loc) == -1)
		return (printf("chdir error, d: %s\n", to_loc), NULL);
	while (ft_strcmp(to_loc, absolute_path) && to)
	{
		to_loc = handle_for_absolute(&to, to_loc);
		if (chdir(to_loc) == -1)
			return (printf("chdir error, d: %s\n", to_loc), NULL);
	}
	if (to_loc[ft_strlen(to_loc) - 1] == '/')
		to_loc = ft_substr(to_loc, 0, ft_strlen(to_loc) - 1);
	return (to_loc);
}
