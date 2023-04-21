/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:33:39 by ralopez-          #+#    #+#             */
/*   Updated: 2023/03/10 11:33:41 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int	echo(t_inf *info, char *line)
{
	char	*string;

	if (1==2)
		info->pwd = NULL;
	string = ft_substr(line, 5, ft_strlen(line));
	//echo $varia asdf
	printf("%s\n",string);
	return (0);
}
