/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:41:20 by ralopez-          #+#    #+#             */
/*   Updated: 2023/03/10 10:41:21 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	prepare_pipes(t_inf *info)
{
	t_command	*tmp;

	tmp = info->commands;
	while (tmp != NULL)
	{
		tmp->fds = malloc(sizeof(int *) * 2);
		if (tmp->fds == NULL || pipe(tmp->fds) != 0)
		{
			//todo free memory de todo lo anterior
			//free_error("error malloc", "", "", info);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	prepare_execution(t_inf *info)
{
	if (info == NULL || info->commands == NULL)
		return (CMD_SUCCESS);
	if (info->commands->cmd == NULL)
	{
		if (info->commands->input_name != NULL || info->commands->output_name != NULL)
			return (CMD_FAILURE);
		return (CMD_SUCCESS);
	}
	if (prepare_pipes(info) == CMD_FAILURE)
		return (CMD_FAILURE);
	return (CMD_NOT_FOUND);
}

//TODO revisar porque no se si es correcto
/*
int	io_sets(t_command *tmp)
{
	if ((tmp->input_name && tmp->input == -2) || (tmp->output_name && tmp->output == -2))
		return (1);
	else
		return (0);
}
*/

int	wait_childs(t_inf *info)
{

	return (0);
}

int	is_builtin(char *cmd)
{
	if (cmd == NULL)
		return (0);
	if (ft_strcmp(cmd, "echo") ==0|| ft_strcmp(cmd, "cd")  ==0|| ft_strcmp(cmd, "pwd")  ==0| 
		ft_strcmp(cmd, "export")  ==0|| ft_strcmp(cmd, "unset")  ==0|| ft_strcmp(cmd, "env") ==0)
		return (1);
}

void	execute_builtin(t_command *cmd, t_inf *info)
{
	if (ft_strcmp(cmd->cmd, "echo"))
		echo(info, "quitaresteargumento", cmd);
	else if (ft_strcmp(cmd->cmd, "cd"))
		cd(info, "quitaresteargumento", cmd);
	else if (ft_strcmp(cmd->cmd, "pwd"))
		pwd(info, cmd);
	else if (ft_strcmp(cmd->cmd, "export"))
		export_binding(info, "quitaresteargumento", cmd);
	else if (ft_strcmp(cmd->cmd, "unset"))
		unset(info, "quitaresteargumento", cmd);
	else if (ft_strcmp(cmd->cmd, "env"))
		env(info, cmd);
}



/** create_cmd:
 * This function create the string with the command to execute
 * Desalocates the memory that dont use.
 */
char	*create_cmd(t_inf *info, int i, char *cmd)
{
	int		len;
	char	*cmd2;
	char	*res;
	char	*sub_string;

	cmd2 = ft_strjoin(info->paths[i], "/");
	len = ft_strlen(ft_strchr(cmd, ' '));
	sub_string = ft_substr(cmd, 0, ft_strlen(cmd) - len);
	res = ft_strjoin(cmd2, sub_string);
	free(cmd2);
	free(sub_string);
	return (res);
}

char	*get_path(char *cmd, t_inf *info)
{
	char	*cmd_ret;
	int		i;

	if (access(cmd, F_OK | X_OK) == 0)
	{
		free(cmd);
		return (cmd);
	}
	i = -1;
	while (info->paths[++i] != NULL)
	{
		cmd_ret = create_cmd(info, i, cmd);
		if (access(cmd_ret, F_OK | X_OK) == 0)
			break ;
		free(cmd_ret);
		cmd_ret = NULL;
	}
	free(cmd);
	return (cmd_ret);
}

void	execute_cmd(t_command *cmd, t_inf *info)
{
	if (cmd != NULL && is_builtin(cmd->cmd))
	{
		execute_builtin(cmd, info);
	}
	else
	{
		cmd->cmd = get_path(cmd->cmd, info);
		printf("execve_cmd:%s\n", cmd->cmd);
		ft_putstr_fd(cmd->cmd, 0);
		
		if (execve(cmd->cmd, cmd->args, info->env) == -1)
		{
			if (cmd != NULL)
				free(cmd);
			msg("Execve", ": ", strerror(errno), info);
		}
	}
}

int	create_childs(t_inf *info)
{
	t_command	*tmp;

	tmp = info->commands;
	while (tmp)
	{
		tmp->pid = fork();
		if (tmp->pid == -1)
			msg("fork", "", strerror(errno), EXIT_FAILURE);
		else if (tmp->pid == 0)
			execute_cmd(tmp, info);
		tmp = tmp->next;
	}
	return (wait_childs(info));
}
/*
int	redir()
{
	int	code;

	code = 0;
	if ()
	if (dup2(in, STDIN_FILENO) == -1)
	{
		//free_error("error", "", "", info);
		code = 1;
	}
	if (dup2(out, STDOUT_FILENO) == -1)
	{
		//free_error("error", "", "", info);
		code = 1;
	}
	return (code);
}*/

int	execute_commands(t_inf *info)
{
	int	code;
	t_command	*tmp;

	code = prepare_execution(info);
	if (code != CMD_NOT_FOUND)
		return (code);
	tmp = info->commands;
/*	if (io_sets(tmp))
		return (false);
	{
		redir(tmp);
		
	}
	if (code == CMD_NOT_FOUND)
		return (CMD_NOT_FOUND);*/
	printf("%s\n", get_path(info->commands->cmd, info));
	code = create_childs(info);
	return (code);
}