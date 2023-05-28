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

	to_location = ft_strdup(pwd);
	tmp = ft_strrchr(to_location, '/');
	if (tmp != NULL)
		*tmp = '\0';
	return ((to_location));
}

char	*handle_cmd_for_change_env_cd(char *arg, char *pwd)
{
	char	*to_location;
	char	*tmp;

	to_location = NULL;
	tmp = NULL;
	tmp = ft_substr(arg, 0, 2);
	if (!ft_strcmp(tmp, "./"))
		arg += 2;
	free(tmp);
	if (arg[ft_strlen(arg) - 1] == '/')
		arg[ft_strlen(arg) - 1] = '\0';
	to_location = ft_strjoin("/", arg);
	tmp = to_location;
	to_location = ft_strjoin(pwd, to_location);
	free(tmp);
	if (chdir(to_location) == -1)
	{
		tmp = to_location;
		to_location = ft_strrchr(to_location, '/') + 1;
		printf("cd: no such file or directory: %s\n", to_location);
		free(tmp);
		return (NULL);
	}
	return (to_location);
}

char	*handle_cd_to_usr(t_inf *info)
{
	char	*to_location;
	char	*usr;
	char	*tmp;
	char	*tmp_free;

	tmp = get_var(info, "USER");
	usr = ft_strjoin("/", tmp);
	free(tmp);
	to_location = handle_back_cd(info->pwd);
	if (chdir(to_location) == -1)
	{
		to_location = ft_strrchr(to_location, '/') + 1;
		printf("cd: no such file or directory: %s\n", to_location);
		return (free(usr), NULL);
	}
	tmp = ft_strrchr(to_location, '/');
	while (ft_strcmp(tmp, usr))
	{
		tmp_free = to_location;
		to_location = handle_back_cd(to_location);
		free(tmp_free);
		if (chdir(to_location) == -1)
		{
			to_location = ft_strrchr(to_location, '/') + 1;
			printf("cd: no such file or directory: %s\n", to_location);
			return (free(usr), NULL);
		}
		tmp = ft_strrchr(to_location, '/');
	}
	free(usr);
	return (ft_strdup(to_location));
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
	free(tmp);
	return (res);
}

char	*handle_absolute_path(char *absolute_path)
{
	char	*to;
	char	*to_loc;
	char	*tmp;

	to = absolute_path;
	to_loc = handle_for_absolute(&to, "");
	if (chdir(to_loc) == -1)
	{
		to_loc = ft_strrchr(to_loc, '/') + 1;
		printf("cd: no such file or directory: %s\n", to_loc);
		return (NULL);
	}
	while (ft_strcmp(to_loc, absolute_path) && to)
	{
		tmp = to_loc;
		to_loc = handle_for_absolute(&to, to_loc);
		free(tmp);
		if (chdir(to_loc) == -1)
		{
			to_loc = ft_strrchr(to_loc, '/') + 1;
			printf("cd: no such file or directory: %s\n", to_loc);
			return (NULL);
		}
	}
	if (to_loc[ft_strlen(to_loc) - 1] == '/')
	{
		tmp = to_loc;
		to_loc = ft_substr(to_loc, 0, ft_strlen(to_loc) - 1);
		free(tmp);	
	}
	free(to);
	return (to_loc);
}
