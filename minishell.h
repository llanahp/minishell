/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 09:47:00 by ralopez-          #+#    #+#             */
/*   Updated: 2023/06/04 23:46:44 by mpizzolo         ###   ########.fr       */
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
# define NOFILE ": No such file or directory"
# define NOCMD ": command not found"

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
	int			must_continue;
	int			last_code;
	int			exit;
}			t_inf;

/** cd.c */
int			cd(t_inf *info, t_command *cmd);
char		*handle_back_cd(char *pwd);
char		*handle_cmd_for_change_env_cd(t_inf *info, char *arg, char *pwd);
char		*handle_absolute_path(t_inf *info, char *absolute_path);
void		handle_no_arg_cd(char **to_location);
void		handle_chdir_error(t_inf *info, char *to_loc, char *free_var);
char		*handle_to_oldpwd(t_inf *info, t_command *cmd);
int			check_home_cd(t_inf *info);
int			check_folder_exists(void);
int			check_folder_exists_err(void);
void		cd_output_error(char *str);
char		*modify_str_for_change_env_cd(t_inf *info, char *arg);
char		*handle_cd_to_first_dir(t_inf *info);
char		*handle_cd_to_home(t_inf *info);
void		manage_cmd_args_cd(t_command *cmd);

/** echo.c */
int			echo(t_command *cmd);

/** pwd.c */
int			pwd(t_inf *info, t_command *cmd);

/** env.c */
int			env(t_inf *info);
int			env_export(t_inf *info);
void		export_binding_err(char *name, char *value, t_command *cmd, int i);
char		*get_value_var_line(char *name, char *line);
int			ft_n_aparitions(char *str, char c);
void		do_export(t_inf *info, char *str, char *name, char *value);

/** export.c */
int			export_binding(t_inf *info, t_command *cmd);

/** unset.c */
int			unset(t_inf *info, t_command *cmd);

/** exit.c */
int			ft_exit(t_command *cmd, t_inf *info);
int			ft_atoi_exit(const char *str);

/** free_split.c */
void		ft_free_split(char **split);
void		ft_free_split2(char ***split);

/** env_utils.c */
void		store_env(t_inf *info, char **env);
int			store_paths(t_inf *info);
int			get_pwd(t_inf *info);
void		change_var_env(t_inf *info, char *var, char *value);
char		*get_var(t_inf *info, char *var);
void		add_var(t_inf *info, char *var, char *value);
int			delete_var(t_inf *info, char *var);
int			exist_var(t_inf *info, char *name);

/** sigaction.c */
void		set_signals_interactive(void);
void		set_signals_noninteractive(void);
void		ignore_sigquit(void);

/** tokenize.c */
int			tokenize(t_inf *info, char *line);

/** token_utils.c */
int			is_space(char c);
int			is_delimiter(char c);
int			is_quote(char c);

/** check_vars.c */
int			check_vars(t_inf *info);
int			delete_quotes(t_inf *info);
int			replace_var(char **str, int i, t_inf *info);
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
void		fds_pipes(int in, int out);

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

char		*replace_string(char *string, char stop, char *new);
char		*get_next_line(int fd);
char		*ft_replace_quotes_2(char **str);
void		ft_delete_char(char *str);
char		*check_var_replace(char *str, t_inf *info);
void		remove_separator(char **str, int sep);
int			is_inside_quotes(char **str, int separator);
int			between_simple_quotes(char *str, int separator);
int			delete_quotes(t_inf *info);
int			check_vars(t_inf *info);
char		*check_var_replace(char *str, t_inf *info);
void		rl_replace_line(const char *text, int clear_undo);
void		extend_var(char **str, t_inf *info);
int			ft_check_char_before(char *line, char c, char z);
int			expand_pox(char *str);
int			num_cmds(t_inf *info);
char		*create_cmd(t_inf *info, int i, char *cmd);
char		*get_path(char *cmd, t_inf *info);
void		clear_command(t_command *cmd);
int			display_error_path(char *cmd_original);
void		store_when_env_null(t_inf *info);
char		*define_delimiter_aux(char **delimiter, t_list **tmp);
char		*define_delimiter(t_list **tmp);
int			ft_error_syntax(t_list *tmp, t_inf *info);
char		*find_name(void);
int			file_exists(char *name);
void		handle_sigint_heredoc(int sig);
int			heredoc_fork(t_inf *info, t_command *command, char *delimiter);
int			parent_heredoc(t_command *command, int *heredoc, int pid);
void		child_heredoc(t_command *command, t_inf *info, int *heredoc, char *deli);
int			read_heredoc(char *name, char *delimiter, t_inf *info);
#endif