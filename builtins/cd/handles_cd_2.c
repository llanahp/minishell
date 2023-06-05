/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handles_cd_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:07:00 by mpizzolo          #+#    #+#             */
/*   Updated: 2023/06/05 12:35:58 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_cd_to_home(t_inf *info)
{
	char	*loc;
	char	*tmp_free;
	char	buf[PATH_MAX];

	if (!check_home_cd(info))
		return (NULL);
	tmp_free = get_var(info, "HOME");
	chdir(tmp_free);
	loc = ft_strdup(getcwd(buf, PATH_MAX));
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
