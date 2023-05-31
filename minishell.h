/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 09:47:00 by ralopez-          #+#    #+#             */
/*   Updated: 2023/05/29 19:02:40 by mpizzolo         ###   ########.fr       */
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
# define LESS 5
# define HEREDOC 6
# define GREATER 7
# define APPEND 8
# define END 9
# define SIMPLE_QUOTE 10
# define DOUBLE_QUOTE 11

typedef struct s_command	t_command;
typedef struct s_inf		t_inf;
t_inf						g_info;

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
	char		**env;
	char		**paths;
	char		*pwd;
	t_list		*tokens;
	t_command	*commands;
	int			pid;
	int			minishell_pid;
	int			last_code;
	int			exit;
}			t_inf;

/** cd.c */
int			cd(t_inf *info, t_command *cmd);
char		*handle_back_cd(char *pwd);
char		*handle_cmd_for_change_env_cd(char *arg, char *pwd);
char		*handle_cd_to_usr(t_inf *info);
char		*handle_absolute_path(char *absolute_path);
void		handle_no_arg_cd(t_command *cmd, char **to_location);
char		*cd_handler(int abs, char *loc, t_command *cmd, t_inf *info);
void		handling_cd(char *to_location, t_command *cmd,
				t_inf *info, int is_abs);
void		handle_chdir_error(char *to_loc, char *free_var);

/** echo.c */
int			echo(t_command *cmd);

/** pwd.c */
int			pwd(t_inf *info, t_command *cmd);

/** env.c */
int			env(t_inf *info);

/** export.c */
int			export_binding(t_inf *info, t_command *cmd);

/** unset.c */
int			unset(t_inf *info, t_command *cmd);

/** exit.c */
void	ft_exit(t_command *cmd, t_inf *info);

/** free_split.c */
void		ft_free_split(char **split);
void		ft_free_split2(char ***split);

/** env_utils.c */
int			get_enviroment(t_inf *info, char **env);
int			get_pwd(t_inf *info);
void		change_var_env(t_inf *info, char *var, char *value);
char		*get_var(t_inf *info, char *var);
void		add_var(t_inf *info, char *var, char *value);
int			delete_var(t_inf *info, char *var);
int			exist_var(t_inf *info, char *name);

/** sigaction.c */
void		set_signals_interactive(void);
void		set_signals_noninteractive(void);

/** tokenize.c */
int			tokenize(t_inf *info, char *line);

/** token_utils.c */
int			is_space(char c);
int			is_delimiter(char c);
int			is_quote(char c);

/** check_vars.c */
int			check_vars(t_inf *info);
int			delete_quotes(t_inf *info);
void		replace_var(char **str, int i, t_inf *info);
void		replace_for_var(char **str, char *value, int index);
void		replace_for_null(char **str, int index);

/** var_utils.c */
int			len_var(char *tmp);
char		*get_name(char *tmp);
void		update_status(char **str, int i, int *status);
char		*get_name_var(char *line);
char		*replace(char *string, char *search, char *replace);

/** create_cmds.c */
int			create_commands(t_inf *info);

/** command_utils.c */
t_command	*ft_lstnew_command(char *cmd);
void		ft_lstadd_back_command(t_command **lst, t_command *new);
void		ft_lstclear_cmds(t_inf *info);
void		ft_lstclear_tokens(t_inf *info);
t_command	*get_last_cmd(t_inf *info);
void		ft_clear_tokens(t_inf *info);

/** save_args.c */
t_list		*save_args(t_list *tmp, t_command *command);
int			num_args(t_list *tmp);
char		**join_arguments(char	**args, char	**tmp);
t_list		*save_word(t_inf *info, t_list *tmp);
void		close_prev_redir(t_command *command);
t_list		*save_input(t_inf *info, t_list *tmp);
t_list		*save_output(t_inf *info, t_list *tmp, int type);
t_list		*save_heredoc(t_inf *info, t_list *tmp);
t_list		*save_pipe(t_inf *info, t_list *tmp, int pipe);

/** ft_error.c */
int			msg(char *str1, char *str2, char *str3, int code);
int			msg_error(char *str1, char *str2, char *str3, int code);
void		end_shell(t_inf *info);
void		free_memory(t_inf *info);

/** execution.c */
int			execute_commands(t_inf *info);

/** pipes.c */
int			prepare_execution(t_inf *info);
int			prepare_pipes(t_inf *info);
int			wait_childs(t_inf *info);
void	fds_pipes(int in, int out);

/** redir.c */
void		redir(t_command *cmd, t_inf *info);
void		close_files(t_command *cmd);
void		redir_files(t_command *cmd);

/** utils */
int			ft_strichr(char *str, char c);
bool		is_separator(char c);
bool		is_var_compliant(char c);
int			is_builtin(char *cmd);
void		puterror(char *cmd, char *msg);

/** quotes.c */
char		*replace_quotes(char *string, char quote);
int			ft_are_double_quotes(char *line);
char		*replace_d_quotes(char *line, char quote);
char		*ft_replace_double_quotes(char *line);

char	*replace_string(char *string, char stop, char *new);
#endif