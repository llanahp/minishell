/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 09:47:00 by ralopez-          #+#    #+#             */
/*   Updated: 2023/03/10 09:47:01 by ralopez-         ###   ########.fr       */
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

# define CMD_NOT_FOUND 127
# define PIPE 3
# define SEMICOLON 4
# define LESS 5
# define HEREDOC 6
# define GREATER 7
# define APPEND 8
# define END 9
# define SIMPLE_QUOTE 10
# define DOUBLE_QUOTE 11

typedef struct s_inf
{
        struct sigaction sa;
        char    **env;
        char	**paths;
        char    *pwd;
        t_list  *tokens;
}               t_inf;

/** cd.c */
int	cd(t_inf *info, char *line);


/** echo.c */
int	echo(t_inf *info, char *line);

/** pwd.c */
int	pwd(t_inf *info);


/** env.c */
int	env(t_inf *info);

/** export.c */
int    	export_binding(t_inf *info, char *line);

/** unset.c */
int unset(t_inf *info, char *line);


void	ft_free_split(char **split);

/** get_info.c */
int	get_enviroment(t_inf *info);
int	get_pwd(t_inf *info);
void	change_var_env(t_inf *info, char *var, char *value);
char	*get_var(t_inf *info, char *var);
void    add_var(t_inf *info, char *var, char *value);
int	delete_var(t_inf *info, char *var);

/** sigaction.c */
void	manejar_sigchild(int signal);
void	init_sigaction(t_inf *info);

/** tokenize.c */
int	tokenize(t_inf *info, char *line);

/** check_vars.c */
int	check_vars(t_inf *info);
int	delete_quotes(t_inf *info);
#endif