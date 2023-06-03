/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handles_cd_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:07:00 by mpizzolo          #+#    #+#             */
/*   Updated: 2023/06/01 15:32:57 by mpizzolo         ###   ########.fr       */
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
	if (tmp != NULL)
		*tmp = '\0';
	return ((to_location));
}

void	handle_chdir_error(char *to_loc, char *free_var)
{
	char	*tmp;

	tmp = to_loc;
	to_loc = ft_strrchr(to_loc, '/') + 1;
	printf("cd: no such file or directory: %s\n", to_loc);
	free(tmp);
	if (free_var != NULL)
		free(free_var);
}

int	check_on_root(t_inf *info)
{
	char	*tmp;
	char	*tmp_free;
	char	*usr;
	int		res;

	tmp_free = get_var(info, "PWD");
	tmp = ft_strrchr(tmp_free, '/') + 1;
	usr = get_var(info, "USER");
	res = !ft_strcmp(tmp, usr);
	free(tmp_free);
	free(usr);
	return (res);
}
