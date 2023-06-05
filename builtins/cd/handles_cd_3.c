/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handles_cd_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:35:58 by mpizzolo          #+#    #+#             */
/*   Updated: 2023/06/05 14:00:34 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
