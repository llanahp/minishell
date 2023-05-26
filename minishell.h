/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 09:47:00 by ralopez-          #+#    #+#             */
/*   Updated: 2023/05/26 16:03:28 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include "get_next_line/get_next_line.h"
# include <readline/history.h>
# include <signal.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>

# define CMD_NOT_FOUND 127

# define CMD_SUCCESS 0
# define CMD_FAILURE 1

# define WORD 0
# define PIPE 3
# define SEMICOLON 4
# define LESS 5
# define HEREDOC 6
# define GREATER 7
# define APPEND 8
# define END 9
# define SIMPLE_QUOTE 10
# define DOUBLE_QUOTE 11
extern int last_code;

typedef struct s_command t_command;


typedef struct s_command
{
	char				*cmd;
	char				**args;
	char				*path;
	int					input;
	int					output;
	int					*redir;
	char				*input_name;
	char				*output_name;
	int					type_redir;
	int					num_cmd_pipe;
	t_command			*previous;
	t_command			*next;
	int					pid;
	int					pipe_out;
		int					*fds;
}		t_command;


typedef struct s_inf
{
	struct sigaction sa;
	char		**env;
	char		**paths;
	char		*pwd;
	t_list		*tokens;
	t_command	*commands;
	int			pid;
}               t_inf;

/** cd.c */
int		cd(t_inf *info, t_command *cmd);
char	*handle_back_cd(char *pwd);
char	*handle_cmd_for_change_env_cd(char *arg, char *pwd);
char	*handle_cd_to_usr(t_inf *info);
char	*handle_absolute_path(char *absolute_path);

/** echo.c */
int	echo(t_command *cmd);

/** pwd.c */
int	pwd(t_inf *info, t_command *cmd);

/** env.c */
int	env(t_inf *info);

/** export.c */
int	export_binding(t_inf *info, t_command *cmd);

/** unset.c */
int 	unset(t_inf *info, t_command *cmd);



void	ft_free_split(char **split);
void	ft_free_split2(char ***split);


/** get_info.c */
int		get_enviroment(t_inf *info);
int		get_pwd(t_inf *info);
void	change_var_env(t_inf *info, char *var, char *value);
char	*get_var(t_inf *info, char *var);
void    add_var(t_inf *info, char *var, char *value);
int		delete_var(t_inf *info, char *var);

/** sigaction.c */
void	set_signals_interactive(void);
void	set_signals_noninteractive(void);

/** tokenize.c */
int	is_quote(char c);
int	tokenize(t_inf *info, char *line);

/** check_vars.c */
int	check_vars(t_inf *info);
int	delete_quotes(t_inf *info);


/** create_cmds.c */
int	create_commands(t_inf *info);

/** command_utils.c */
t_command	*ft_lstnew_command(char *cmd);
void		ft_lstadd_back_command(t_command **lst, t_command *new);
void		ft_lstclear_cmds(t_inf *info);
void		ft_lstclear_tokens(t_inf *info);
t_command	*get_last_cmd(t_inf *info);
void	ft_clear_tokens(t_inf *info);


/** save_args.c */
t_list *save_args(t_list *tmp, t_command *command);
int		num_args(t_list *tmp);
char	**join_arguments(char	**args, char	**tmp);

t_list	*save_word(t_inf *info, t_list *tmp);

void	close_prev_redir(t_command *command);
t_list	*save_input(t_inf *info, t_list *tmp);

t_list	*save_output(t_inf *info, t_list *tmp, int type);

t_list	*save_heredoc(t_inf *info, t_list *tmp);

t_list	*save_pipe(t_inf *info, t_list *tmp, int pipe);

/** ft_error.c */
int	msg(char *str1, char *str2, char *str3, int code);


char	*get_next_line(int fd);


/** execution.c */
int execute_commands(t_inf *info);


/** pipes.c */
int	prepare_execution(t_inf *info);
int	prepare_pipes(t_inf *info);
int	wait_childs(t_inf *info);

/** redir.c */
void	redir(t_command *cmd, t_inf *info);

int	is_builtin(char *cmd);

/** utils */
int	ft_strichr(char *str, char c);

#endif