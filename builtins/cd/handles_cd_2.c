/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handles_cd_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:07:00 by mpizzolo          #+#    #+#             */
/*   Updated: 2023/06/04 23:40:53 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_chdir_error(t_inf *info, char *to_loc, char *free_var)
{
	char	*tmp;

	info->last_code = 127;
	tmp = to_loc;
	to_loc = ft_strrchr(to_loc, '/') + 1;
	cd_output_error(to_loc);
	free(tmp);
	if (free_var != NULL)
		free(free_var);
}

char	*handle_to_oldpwd(t_inf *info, t_command *cmd)
{
	char	*res;
	char	*tmp;
	int		fd_write;

	if (exist_var(info, "OLDPWD") == 1)
	{
		res = get_var(info, "OLDPWD");
		if (chdir(res) == -1)
			return (handle_chdir_error(info, res, res), NULL);
		fd_write = 1;
		if (cmd->output != -2)
			fd_write = cmd->output;
		tmp = ft_strjoin(res, "\n");
		ft_putstr_fd(tmp, fd_write);
		free(tmp);
		return (res);
	}
	ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
	info->last_code = 127;
	return (NULL);
}

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
