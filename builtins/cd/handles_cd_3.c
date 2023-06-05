/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handles_cd_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:35:58 by mpizzolo          #+#    #+#             */
/*   Updated: 2023/06/03 20:41:30 by mpizzolo         ###   ########.fr       */
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