# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/21 12:09:04 by gbaumgar          #+#    #+#              #
#    Updated: 2022/10/26 14:45:54 by gbaumgar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

USER			= gbaumgar

NAME			= minishell

INC_DIR			= ./include/
SRC_DIR			= ./src/
OUT_DIR			= ./

SRC				= main.c signal.c shell_init.c
OBJS			= ${SRC:%.c=${OUT_DIR}%.o}

INCLUDE			= -I${INC_DIR}
LIBFT			= -Llibft -lft	
READLINE		= -L/Users/${USER}/.brew/opt/readline/lib -lreadline
READLINE_INC	= -I/Users/${USER}/.brew/opt/readline/include

CC				= gcc
CFLAGS			= -Wall -Wextra -Werror -g
# CFLAGS			+= -fsanitize=address
RM				= rm -f


all: ${NAME}

${NAME}: ${OBJS}
	make -C libft
	${CC} -o ${NAME} ${LIBFT} ${READLINE} ${INCLUDE} ${OBJS} ${CFLAGS}

${OUT_DIR}%.o: ${SRC_DIR}%.c 
	${CC} ${CFLAGS} ${INCLUDE} ${READLINE_INC} $< -c -o $@

clean:
	make clean -C libft
	${RM} ${OBJS}

fclean:	clean
	make fclean -C libft
	${RM} ${NAME}

re: fclean ${NAME}

bonus:	all

.PHONY:	all clean fclean re bonus
