# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/13 15:39:30 by ralopez-          #+#    #+#              #
#    Updated: 2023/06/01 12:53:59 by mpizzolo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS = ft_isalpha.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_strlen.c ft_isdigit.c ft_bzero.c ft_toupper.c ft_tolower.c ft_memcpy.c \
	ft_atoi.c ft_strlcpy.c ft_calloc.c ft_strncmp.c ft_memchr.c ft_memcmp.c\
	ft_strrchr.c ft_strnstr.c ft_strlcat.c ft_strdup.c ft_strchr.c \
	ft_memmove.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
	ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c ft_memset.c  ft_strcmp.c ft_strcontains.c \
	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

CC = gcc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror -g  
OBJS = ${SRCS:.c=.o}
AR = ar -rcs


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

.c.o:
	@echo $(GREEN) Compiling file $< $(COLRESET)
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	@${AR} ${NAME} ${OBJS}

clean:
	@echo $(RED) clean libft $(COLRESET)
	@${RM} ${OBJS}



fclean: clean
	@echo $(RED) fclean libft $(COLRESET)
	@${RM} ${NAME}

re:	fclean all

.PHONY : all clean fclean re 
