/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:34:31 by ralopez-          #+#    #+#             */
/*   Updated: 2023/06/03 15:34:32 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	store_env(t_inf *info, char **env)
{
	int	i;
	int	j;

	i = 0;
	if (env[0] == NULL)
	{
		store_when_env_null(info);
		return ;
	}
	while (env[i])
		i++;
	info->env = (char **)malloc(sizeof(char *) * (i));
	if (! info->env)
		return ;
	i = -1;
	j = 0;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
		{
			if (ft_atoi(env[i] + 6) < 0)
				info->env[j++] = ft_strdup("SHLVL=0");
			else
				info->env[j++] = ft_strjoin("SHLVL=", ft_itoa(ft_atoi(env[i] + 6) + 1));
		}
		else if (ft_strncmp(env[i], "OLDPWD=", 7))
			info->env[j++] = ft_strdup(env[i]);
	}
	info->env[j] = NULL;
}
