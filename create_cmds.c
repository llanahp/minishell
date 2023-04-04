/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:41:40 by ralopez-          #+#    #+#             */
/*   Updated: 2023/03/31 10:41:42 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "minishell.h"

void mostrar_commands(t_inf *info)
{
	printf("--------------\n");
	while (info->commands)
	{
		printf("%s\n", (char *)info->commands->cmd);
		info->tokens = info->tokens->next;
	}
}

t_command	*get_last_cmd(t_inf *info)
{
	t_command	*tmp;
	if (info->commands == NULL)
	{
		tmp = malloc(sizeof(t_command) * 1);
		if (!tmp)
			return (NULL);
		ft_lstadd_back_command(info->commands, tmp);
		return (tmp);
	}
	tmp = info->commands;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	return (tmp);
}

int	num_args(t_list *tmp)
{
	int i;

	i = 0;
	while (tmp && tmp->type == WORD)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

t_list *save_args(t_list *tmp, t_command *command)
{
	int i;

	i = 0;
	command->args = (char **)malloc(sizeof(char *) * num_args(tmp));
	while (tmp && tmp->type == WORD)
	{
		command->args[i] = ft_strdup(tmp->content);
		printf("args(%d)%s\n",i, command->args[i]);
		tmp = tmp->next;
		i++;
	}
	command->args[i] = NULL;
	return (tmp);
}

t_list *save_word(t_inf *info, t_list *tmp)
{
	t_command *command;
	command = get_last_cmd(info);
	command->cmd = ft_strdup(tmp->content);
	printf("cmd:%s\n", command->cmd);
	tmp = tmp->next;
	tmp  = save_args( tmp, command);
	return (tmp);
}


int	create_commands(t_inf *info)
{
	if (info->tokens == NULL)
		return (0);
	t_list	*tmp;
	tmp = info->tokens;
	while (tmp)
	{
		printf("->%s (%d)\n",tmp->content, tmp->type);
		if (tmp->type == WORD)
		{
			printf("Antes de guardar\n");
			tmp  = save_word(info, tmp);
			printf("Almacenado\n");
			getchar();
		}
		/*else if (tmp->type == PIPE || tmp->type == SEMICOLON)
		{
			tmp = tmp->next;
			continue;
		}
		else if (tmp->type == HEREDOC || tmp->type == APPEND)
		{
			tmp = tmp->next;
			continue;
		}
		else if (tmp->type == LESS || tmp->type == GREATER)
		{
			tmp = tmp->next;
			continue;
		}*/
		else if (tmp->type == END)
		{
			break;
		}
		
		/*else
		{
			ft_lstadd_back(&info->commands, ft_lstnew(tmp->content));
			tmp = tmp->next;
		}*/
		mostrar_commands(info);
	}
	return (0);
}