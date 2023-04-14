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
	t_command	*tmp;

	tmp = info->commands;
	printf("--------------\n");
	while (tmp != NULL)
	{
		printf("cmd:%s\n", (char *)tmp->cmd);
		int i=0;
		while (tmp->args[i] != NULL)
		{
			printf("args(%d): %s\n",i, tmp->args[i]);
			i++;
		}
		tmp = tmp->next;
		
	}
}

t_command	*get_last_cmd(t_inf *info)
{
	t_command	*tmp;
	if (info->commands == NULL)
	{
		/*tmp = (t_command *)malloc(sizeof(t_command) * 1);
		if (!tmp)
			return (NULL);*/
		tmp = ft_lstnew_command(NULL);
		ft_lstadd_back_command(&info->commands, tmp);
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

char	**join_arguments(char	**args, char	**tmp)
{
	int	i;
	int	j;
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
	if (tmp2 == NULL)
		return (NULL);
	i = 0;
	j = 0;
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

t_list *save_args(t_list *tmp, t_command *command)
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

t_list	*save_word(t_inf *info, t_list *tmp)
{
	t_command *command;
	command = get_last_cmd(info);
	if (command->cmd != NULL)
	{
		printf("cmd : %s\n", command->cmd);
	}
	if (command->cmd == NULL)
	{
		command->cmd = ft_strdup(tmp->content);
		tmp = tmp->next;
		tmp  = save_args(tmp, command);
	}
	else
		tmp  = save_args(tmp, command);
	return (tmp);
}


t_list	*save_input(t_inf *info, t_list *tmp)
{
	t_command *command;
	command = get_last_cmd(info);
	tmp = tmp->next;
	if (command->input_name != NULL)
	{
		close(command->input);
		free(command->input_name);
		command->input_name = NULL;
	}
	if (tmp != NULL && tmp->type == WORD)
	{
		command->input_name = ft_strdup(tmp->content);
		if (command->input_name == NULL)
			printf("Entrada no valida");
		else
		{
			command->input = open(command->input_name, O_RDONLY);
			if (command->input == -1)
			{
				perror("Error al abrir el archivo de entrada");
			}
		}
		tmp = tmp->next;
	}
	else
		command->input_name = NULL;
	return (tmp);
}

t_list	*save_output(t_inf *info, t_list *tmp)
{
	t_command *command;
	command = get_last_cmd(info);
	tmp = tmp->next;
	if (command->output_name != NULL)
	{
		close(command->output);
		free(command->output_name);
		command->output_name = NULL;
	}
	if (tmp != NULL && tmp->type == WORD)
	{
		command->output_name = ft_strdup(tmp->content);
		if (command->output_name == NULL)
			printf("salida no valida");
		else
		{
			command->output = open(command->output_name,  O_WRONLY | O_CREAT | O_TRUNC, 0664);
			if (command->output == -1)
			{
				perror("Error al abrir el archivo de salida");
			}
		}
		tmp = tmp->next;
	}
	else
		command->output_name = NULL;
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
		if (tmp != NULL && tmp->type == WORD)
			tmp  = save_word(info, tmp);
		else if (tmp->type == LESS)
			tmp  = save_input(info, tmp);
		else if (tmp->type == GREATER)
			tmp  = save_output(info, tmp);
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
		*/
		else if (tmp != NULL && tmp->type == END)
		{
			break;
		}
		
		/*else
		{
			ft_lstadd_back(&info->commands, ft_lstnew(tmp->content));
			tmp = tmp->next;
		}*/
		
	}

	mostrar_commands(info);
	return (0);
}