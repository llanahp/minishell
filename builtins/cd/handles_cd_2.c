/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handles_cd_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:07:00 by mpizzolo          #+#    #+#             */
/*   Updated: 2023/06/03 19:16:50 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_no_arg_cd(char **to_location)
{
	*to_location = ft_strdup("~");
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

void	handle_chdir_error(char *to_loc, char *free_var)
{
	char	*tmp;

	tmp = to_loc;
	to_loc = ft_strrchr(to_loc, '/') + 1;
	cd_output_error(to_loc);
	free(tmp);
	if (free_var != NULL)
		free(free_var);
}

int	check_on_home(t_inf *info)
{
	char	*tmp;
	char	*tmp_free;
	char	*usr;
	int		res;

	tmp_free = get_var(info, "PWD");
	tmp = ft_strrchr(tmp_free, '/') + 1;
	free(tmp_free);
	tmp_free = get_var(info, "HOME");
	usr = tmp_free;
	while (usr[0] == '/')
		usr = ft_strrchr(usr, '/') + 1;
	res = !ft_strcmp(tmp, usr);
	free(tmp_free);
	return (res);
}

char	*handle_to_oldpwd(t_inf *info)
{
	char	*res;

	if (exist_var(info, "OLDPWD") == 1)
	{
		res = get_var(info, "OLDPWD");
		if (chdir(res) == -1)
		{
			info->last_code = 127;
			return (handle_chdir_error(res, res), NULL);
		}
		printf("%s\n", res);
		return (res);
	}
	ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
	info->last_code = 127;
	return (NULL);
}
