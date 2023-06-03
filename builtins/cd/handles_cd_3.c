/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handles_cd_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:35:58 by mpizzolo          #+#    #+#             */
/*   Updated: 2023/06/03 19:02:37 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_home_cd(t_inf *info)
{
	if (!exist_var(info, "HOME"))
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		info->last_code = 1;
		return (0);
	}
	return (1);
}

char	*checking_for_env(char *tmp, char *usr, t_inf *info)
{
	char	*tmp_free;
	char	*to_location;

	to_location = handle_back_cd(info->pwd);
	if (chdir(to_location) == -1)
	{
		info->last_code = 127;
		return (handle_chdir_error(to_location, usr), NULL);
	}
	tmp = ft_strrchr(to_location, '/');
	while (ft_strcmp(tmp, usr))
	{
		tmp_free = to_location;
		to_location = handle_back_cd(to_location);
		free(tmp_free);
		if (chdir(to_location) == -1)
		{
			info->last_code = 127;
			return (handle_chdir_error(to_location, usr), NULL);
		}
		tmp = ft_strrchr(to_location, '/');
	}
	return (to_location);
}

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
