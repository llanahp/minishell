/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handles_cd_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:35:58 by mpizzolo          #+#    #+#             */
/*   Updated: 2023/06/03 18:13:59 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_home_cd(t_inf *info)
{
	if (!exist_var(info, "HOME"))
	{
		printf("minishell: cd: HOME not set");
		info->last_code = 1;
		return (0);
	}
	return (1);
}

char	*checking_for_home(char *tmp, char *usr, t_inf *info)
{
	char	*tmp_free;
	char	*to_location;

	to_location = handle_back_cd(info->pwd);
	if (chdir(to_location) == -1)
		return (handle_chdir_error(to_location, usr), NULL);
	tmp = ft_strrchr(to_location, '/');
	while (ft_strcmp(tmp, usr))
	{
		tmp_free = to_location;
		to_location = handle_back_cd(to_location);
		free(tmp_free);
		if (chdir(to_location) == -1)
			return (handle_chdir_error(to_location, usr), NULL);
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
		printf("cd: error retrieving current directory: ");
		printf("getcwd: No such file or directory\n");
		return (127);
	}
	return (0);
}
