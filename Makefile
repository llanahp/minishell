# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/27 12:35:10 by ralopez-          #+#    #+#              #
#    Updated: 2023/05/26 16:01:11 by mpizzolo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -g -I libft/  #-Werror

LDFLAGS		= -L/Users/$(USER)/.brew/opt/readline/lib
CPPFLAGS	= -I/Users/$(USER)/.brew/opt/readline/include


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

SRC = builtins/echo.c builtins/cd/cd.c builtins/cd/handles_cd.c builtins/pwd.c builtins/env.c builtins/export.c builtins/unset.c \
	token/token_utils.c token/tokenize.c \
	utils/utils.c utils/quotes.c\
	vars/check_vars.c vars/var_utils.c\
	commands/save_args.c commands/save_heredoc.c  commands/save_input.c commands/save_output.c commands/save_pipe.c commands/save_word.c\
	ft_error.c execution.c redir.c ft_pipes.c ft_free_split.c env_utils.c sigaction.c create_cmds.c command_utils.c \
	minishell.c

OBJ = $(SRC:.c=.o)


%.o: %.c
	@echo $(GREEN) Compiling file $< $(COLRESET)
	@$(CC) $(CFLAGS) -c $< -o $@ 

$(NAME): $(OBJ) libft
	@echo $(BLUE) Done!!! $(COLRESET)
	@$(CC) -o $@ $(OBJ) -Llibft -lft $(LDFLAGS) $(CPPFLAGS) -lreadline

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