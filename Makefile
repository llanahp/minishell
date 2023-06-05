# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/27 12:35:10 by ralopez-          #+#    #+#              #
#    Updated: 2023/06/03 20:41:51 by mpizzolo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -g  -I libft/  #-Werror 

UNAME := $(shell uname -s)

ifeq ($(UNAME), Darwin)
    # Check for macOS version
    MACOS_VERSION := $(shell sw_vers -productVersion | cut -d. -f1)
    ifeq ($(MACOS_VERSION), 13)
        # macOS Ventura (13.x)
        LDFLAGS     = -L/opt/homebrew/Cellar/readline/8.2.1/lib
        CPPFLAGS    = -I/opt/homebrew/Cellar/readline/8.2.1/include
        $(info Using macOS Ventura paths)
    else
        # Other macOS versions (assume macOS Silicon)
        LDFLAGS     = -L/Users/$(USER)/.brew/opt/readline/lib
        CPPFLAGS    = -I/Users/$(USER)/.brew/opt/readline/include
        $(info Using macOS Silicon paths)
    endif
else
    # Non-Darwin systems
    LDFLAGS     = -L/default/path/to/readline/lib
    CPPFLAGS    = -I/default/path/to/readline/include
    $(info Using default paths for non-Darwin systems)
endif




ifdef TERM
RED			:=	"\033[1;31m"
GREEN		:=	"\033[0;32m"
BGREEN		:=	"\033[1;32m"
BLUE		:=	"\033[0;34m"
YELLOW		:=	"\033[0;33m"
PURPLE		:=	"\033[0;35m"
CYAN		:=	"\033[0;36m"
GREY		:=	"\033[0;37m"
# When printed reset the color
COLRESET	:=	"\033[0m"
endif

SRC = builtins/echo.c builtins/cd/cd.c builtins/cd/handles_cd.c builtins/cd/handles_cd_2.c builtins/cd/handles_cd_3.c builtins/cd/handles_cd_4.c  builtins/pwd.c builtins/env.c builtins/export/export.c builtins/export/export_2.c builtins/unset.c builtins/exit.c\
	token/ft_token_utils.c token/ft_tokenize.c \
	utils/ft_utils.c utils/ft_quotes.c utils/ft_quotes_2.c utils/ft_atoi_exit.c\
	vars/ft_check_vars.c vars/ft_var_utils.c vars/ft_var_utils2.c vars/ft_check_vars2.c vars/ft_check_vars3.c\
	commands/save_args.c commands/save_heredoc.c  commands/save_input.c commands/save_output.c commands/save_pipe.c commands/save_word.c\
	ft_error.c ft_execution.c ft_redir.c ft_pipes.c ft_free_split.c ft_env_utils.c ft_sigaction.c ft_create_cmds.c ft_command_utils.c \
	ft_execution2.c ft_env_utils2.c ft_command_utils2.c ft_env_utils3.c utils/ft_quotes3.c commands/save_heredoc2.c \
    ft_sigaction_here.c commands/save_heredoc3.c minishell.c

OBJ = $(SRC:.c=.o)


%.o: %.c
	@echo $(GREEN) Compiling file $< $(COLRESET)
	@$(CC) $(CFLAGS) -c $< -o $@ 

$(NAME): $(OBJ) libft
	@echo $(BLUE) Done!!! $(COLRESET)
	@$(CC) -o $@ $(OBJ) $(CFLAGS) -Llibft -lft $(LDFLAGS) $(CPPFLAGS) -lreadline

libft:
	@make -C libft 


all : $(NAME)

re : fclean all

clean :
	@echo $(RED) clean $(COLRESET)
	make clean -C libft/
	@$(RM) $(OBJ)

fclean : clean
	@echo $(RED) fclean $(COLRESET)
	@$(RM) $(NAME) libft/libft.a

.PHONY: all clean fclean re libft