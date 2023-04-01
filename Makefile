# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/27 12:35:10 by ralopez-          #+#    #+#              #
#    Updated: 2023/01/27 12:35:13 by ralopez-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra #-Werror

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

SRC = libft/ft_isalpha.c libft/ft_isalnum.c libft/ft_isascii.c libft/ft_isprint.c \
	libft/ft_strlen.c libft/ft_isdigit.c libft/ft_bzero.c libft/ft_toupper.c \
	libft/ft_tolower.c libft/ft_memcpy.c libft/ft_atoi.c libft/ft_strlcpy.c \
	libft/ft_calloc.c libft/ft_strncmp.c libft/ft_memchr.c libft/ft_memcmp.c\
	libft/ft_strrchr.c libft/ft_strnstr.c libft/ft_strlcat.c libft/ft_strdup.c \
	libft/ft_strchr.c libft/ft_memmove.c libft/ft_substr.c libft/ft_strjoin.c \
	libft/ft_strtrim.c libft/ft_split.c libft/ft_itoa.c libft/ft_strmapi.c \
	libft/ft_striteri.c libft/ft_putchar_fd.c libft/ft_putstr_fd.c \
	libft/ft_putendl_fd.c libft/ft_putnbr_fd.c libft/ft_memset.c \
	libft/ft_lstnew.c libft/ft_lstadd_front.c libft/ft_lstsize.c \
	libft/ft_lstlast.c libft/ft_lstadd_back.c libft/ft_lstdelone.c \
	libft/ft_lstclear.c libft/ft_lstiter.c libft/ft_lstmap.c \
	libft/ft_strcmp.c libft/ft_strcontains.c\
	builtins/echo.c builtins/cd.c builtins/pwd.c builtins/env.c builtins/export.c builtins/unset.c \
	ft_free_split.c get_info.c sigaction.c tokenize.c check_vars.c\
	minishell.c

OBJ = $(SRC:.c=.o)


%.o: %.c
	@echo $(GREEN) Compiling file $< $(COLRESET)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@echo $(BLUE) Done!!! $(COLRESET)
	@$(CC) $(CFLAGS) $(OBJ) $(MLX) -o $(NAME) -l readline

all : $(NAME)

re : fclean all

clean :
	@echo $(RED) clean $(COLRESET)
	@$(RM) $(OBJ)

fclean : clean
	@echo $(RED) fclean $(COLRESET)
	@$(RM) $(NAME)

.PHONY: all clean fclean re