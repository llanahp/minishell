/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:41:20 by ralopez-          #+#    #+#             */
/*   Updated: 2023/03/10 10:41:21 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int	unset(t_inf *info, char *line, t_command *cmd)
{
	char	**args;
	int     i;
	int		code;

	i = 1;
	args = ft_split(line, ' ');
	code  = 0;
	while (args[i])
	{
		if (delete_var(info, args[i]) == 1 && code == 0)
			code = 1;
		i++;
	}
	ft_free_split(args);
	return (code);
}