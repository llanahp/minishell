/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handles_cd_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 18:20:12 by mpizzolo          #+#    #+#             */
/*   Updated: 2023/06/05 14:10:59 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_folder_exists(void)
{
	char	buf[PATH_MAX];

	if (getcwd(buf, sizeof(buf)) == NULL)
		return (127);
	return (0);
}

int	check_folder_exists_err(void)
{
	char	buf[PATH_MAX];

	if (getcwd(buf, sizeof(buf)) == NULL)
	{
		ft_putstr_fd("minishell: cd: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: No such file or directory\n", 2);
		return (127);
	}
	return (0);
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

char	*prepare_abs(char *abs, char **to)
{
	char	*tmp;
	char	*to_loc;

	tmp = NULL;
	if (abs[ft_strlen(abs) - 1] != '/')
	{
		abs = ft_strjoin(abs, "/");
		tmp = abs;
	}
	to_loc = handle_for_absolute(&abs, "");
	if (tmp != NULL)
		free(tmp);
	*to = abs;
	return (to_loc);
}

char	*handle_absolute_path(t_inf *info, char *absolute_path)
{
	char	*to;
	char	*to_loc;
	char	*tmp;

	to_loc = prepare_abs(absolute_path, &to);
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
