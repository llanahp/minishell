/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:08:25 by ralopez-          #+#    #+#             */
/*   Updated: 2023/03/31 14:08:27 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*save_args(t_list *tmp, t_command *command)
{
	int		i;
	char	**tmp2;

	i = 0;
	tmp2 = (char **)malloc(sizeof(char *) * (num_args(tmp) + 1));
	if (tmp2 == NULL)
		return (NULL);
	while (tmp && tmp->type == WORD)
	{
		tmp2[i] = ft_strdup(tmp->content);
		tmp = tmp->next;
		i++;
	}
	tmp2[i] = NULL;
	command->args = join_arguments(command->args, tmp2);
	return (tmp);
}

int	num_args(t_list *tmp)
{
	int	i;

	i = 0;
	while (tmp && tmp->type == WORD)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**malloc_join_args(char **args, char **tmp)
{
	int		i;
	int		j;
	char	**tmp2;

	i = 0;
	j = 0;
	if (args == NULL && tmp == NULL)
		return (NULL);
	while (args && args[i] != NULL)
		i++;
	while (tmp && tmp[j] != NULL)
		j++;
	tmp2 = (char **)malloc(sizeof(char *) * (i + j + 1));
	return (tmp2);
}

char	**join_arguments(char **args, char **tmp)
{
	int		i;
	int		j;
	char	**tmp2;

	i = 0;
	j = 0;
	tmp2 = malloc_join_args(args, tmp);
	if (tmp2 == NULL)
		return (NULL);
	while (args && args[i] != NULL)
	{
		tmp2[i] = ft_strdup(args[i]);
		i++;
	}
	while (tmp && tmp[j] != NULL)
	{
		tmp2[i] = ft_strdup(tmp[j]);
		i++;
		j++;
	}
	tmp2[i] = NULL;
	ft_free_split(args);
	ft_free_split(tmp);
	return (tmp2);
}
