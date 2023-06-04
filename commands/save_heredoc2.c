/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_heredoc2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 19:03:30 by ralopez-          #+#    #+#             */
/*   Updated: 2023/06/03 19:03:31 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*define_delimiter_aux(char **delimiter, t_list **tmp)
{
	int		quote;

	quote = (*tmp)->type;
	(*tmp) = (*tmp)->next;
	while ((*tmp) && (*tmp)->type != quote)
	{
		(*delimiter) = ft_strjoin((*delimiter), (*tmp)->content);
		(*tmp) = (*tmp)->next;
	}
	if ((*tmp)->type != quote)
	{
		free((*delimiter));
		return (NULL);
	}
	return ((*delimiter));
}

char	*define_delimiter(t_list **tmp)
{
	char	*delimiter;

	if (!(*tmp))
		return (NULL);
	if ((*tmp)->type == WORD)
	{
		delimiter = ft_strdup((*tmp)->content);
		(*tmp) = (*tmp)->next;
		return (delimiter);
	}
	else if ((*tmp)->type == SIMPLE_QUOTE || (*tmp)->type == DOUBLE_QUOTE)
		return (define_delimiter_aux(&delimiter, tmp));
	else
		return (NULL);
}

char	*find_name(void)
{
	float	i;
	char	*name;
	char	*n;

	i = 0;
	n = ft_itoa(i);
	name = ft_strjoin("/tmp/heredoc_", n);
	while (file_exists(name))
	{
		if (name != NULL)
			free(name);
		if (n != NULL)
			free(n);
		i++;
		n = ft_itoa(i);
		name = ft_strjoin("/tmp/heredoc_", n);
	}
	if (n != NULL)
		free(n);
	return (name);
}

int	file_exists(char *name)
{
	if (access(name, F_OK) == 0)
		return (1);
	else
		return (0);
}
