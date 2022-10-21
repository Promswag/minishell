# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/21 12:09:04 by gbaumgar          #+#    #+#              #
#    Updated: 2022/10/21 12:09:30 by gbaumgar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

INCLUDE_DIR		= ./include/
SRC_DIR			= ./src/
OUT_DIR			= ./

SRC				= main.c
OBJS			= ${SRC:%.c=${OUT_DIR}%.o}

INCLUDE			= -I${INCLUDE_DIR}	

CC				= gcc
CFLAGS			= -Wall -Wextra -Werror -g
# CFLAGS			+= -fsanitize=address
RM				= rm -f

all: ${NAME}

${NAME}: ${OBJS}
	${CC} -o ${NAME} ${INCLUDE} ${OBJS} ${CFLAGS}

${OUT_DIR}%.o: ${SRC_DIR}%.c 
	${CC} ${CFLAGS} ${INCLUDE} $< -c -o $@

clean:
	${RM} ${OBJS}

fclean:	clean
	${RM} ${NAME}

re: fclean ${NAME}

bonus:	all

.PHONY:	all clean fclean re bonus
