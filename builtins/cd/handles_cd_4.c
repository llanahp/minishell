/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handles_cd_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 18:20:12 by mpizzolo          #+#    #+#             */
/*   Updated: 2023/06/03 19:12:10 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_user_cd(t_inf *info)
{
	if (!exist_var(info, "USER"))
	{
		ft_putstr_fd("minishell: cd: USER not set\n", 2);
		info->last_code = 1;
		return (0);
	}
	return (1);
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

char	*handle_cd_to_usr(t_inf *info)
{
	char	*to_location;
	char	*usr;
	char	*tmp;
	char	*tmp_free;

	if (!check_user_cd(info))
		return (NULL);
	tmp = get_var(info, "USER");
	usr = ft_strjoin("/", tmp);
	tmp_free = tmp;
	if (check_on_root(info) == 1)
		return (free(usr), NULL);
	to_location = checking_for_env(tmp, usr, info);
	free(tmp_free);
	free(usr);
	return (to_location);
}

void	cd_output_error(char *str)
{
	char	*tmp;

	ft_putstr_fd("minishell: cd: ", 2);
	if (str)
	{	
		tmp = ft_substr(str, 0, 2);
		if (!ft_strcmp(tmp, "./"))
		{
			str = ft_substr(str, 2, ft_strlen(str));
			free(str);
		}
		ft_putstr_fd(str, 2);
		free(tmp);
	}
	ft_putstr_fd("No such file or directory\n", 2);
}
