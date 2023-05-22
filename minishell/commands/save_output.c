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

t_list	*save_output(t_inf *info, t_list *tmp, int type)
{
	t_command	*command;

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
			command->output = open(command->output_name,  O_WRONLY | O_CREAT | type, 0664);
			if (command->output == -1)
				perror("Error al abrir el archivo de salida");
		}
		tmp = tmp->next;
	}
	else
		command->output_name = NULL;
	return (tmp);
}
