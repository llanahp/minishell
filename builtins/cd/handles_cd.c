/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handles_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:57:41 by mpizzolo          #+#    #+#             */
/*   Updated: 2023/06/04 23:29:38 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*handle_for_absolute(char **to, char *to_loc)
{
	char	*res;
	char	*tmp;
	int		i_tmp;

	i_tmp = ft_strichr(to[0] + 1, '/');
	if (i_tmp != -1)
		tmp = ft_substr(to[0], 0, ft_strlen(to[0]));
	else
		tmp = ft_substr(to[0], 0, i_tmp + 1);
	to[0] = ft_strchr(to[0] + 1, '/');
	res = ft_strjoin(to_loc, tmp);
	free(tmp);
	return (res);
}

char	*handle_absolute_path(t_inf *info, char *absolute_path)
{
	char	*to;
	char	*to_loc;
	char	*tmp;

	to = absolute_path;
	to_loc = handle_for_absolute(&to, "");
	if (chdir(to_loc) == -1)
		return (handle_chdir_error(info, to_loc, to), NULL);
	while (ft_strcmp(to_loc, absolute_path) && to)
	{
		tmp = to_loc;
		free(to);
		to_loc = handle_for_absolute(&to, to_loc);
		free(tmp);
		if (chdir(to_loc) == -1)
			return (handle_chdir_error(info, to_loc, to), NULL);
	}
	if (to_loc[ft_strlen(to_loc) - 1] == '/')
		to_loc[ft_strlen(to_loc) - 1] = '\0';
	return (free(to), to_loc);
}

char	*handle_cd_to_home(t_inf *info)
{
	char	*loc;
	char	*tmp_free;

	if (!check_home_cd(info))
		return (NULL);
	tmp_free = get_var(info, "HOME");
	loc = handle_absolute_path(info, tmp_free);
	free(tmp_free);
	return (loc);
}

char	*handle_back_cd(char *pwd)
{
	char	*to_location;
	char	*tmp;

	to_location = ft_strdup(pwd);
	tmp = ft_strrchr(to_location, '/');
	if (tmp != NULL && ft_strcmp(tmp, "/Users") && ft_strcmp(tmp, "/"))
		*tmp = '\0';
	else
		return (ft_strdup("/"));
	return ((to_location));
}
