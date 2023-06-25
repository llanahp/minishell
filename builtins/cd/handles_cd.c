/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handles_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:57:41 by mpizzolo          #+#    #+#             */
/*   Updated: 2023/06/05 13:58:31 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_home_cd(t_command *cmd, t_inf *info, int *is_abs)
{
	char	*home;
	char	*res;
	char	*str;

	str = cmd->args[0];
	home = get_var(info, "HOME");
	str = ft_substr(str, 1, ft_strlen(str));
	res = ft_strjoin(home, str);
	free(home);
	free(str);
	str = cmd->args[0];
	cmd->args[0] = res;
	free(str);
	*is_abs = 1;
	return (ft_strdup(res));
}

int	chdir_exeptions(char *str)
{
	int	res;

	res = 0;
	if (!ft_strcmp(str, "--"))
		res = 1;
	else if (!ft_strcmp(str, "~"))
		res = 1;
	else if (!ft_strcmp(str, "-"))
		res = 1;
	return (res);
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
