# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/21 12:09:04 by gbaumgar          #+#    #+#              #
#    Updated: 2022/10/28 16:55:19 by gbaumgar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

INC_DIR			= ./include/
SRC_DIR			= ./src/
OUT_DIR			= ./obj/

SRC				= 	main.c \
					shell_init.c \
					signal.c \
					builtins/ms_echo.c \
					builtins/ms_export.c \
					# pars/ms_errors.c \
					# pars/ms_parsing.c \
					# pars/ms_syntx.c

SRCC			= ${addprefix ${SRC_DIR}, ${SRC}}
OBJS			= ${SRCC:%.c=${OUT_DIR}%.o}

INCLUDE			= -I${INC_DIR}
LIBFT			= -Llibft -lft	
READLINE		= -L/Users/${USER}/.brew/opt/readline/lib -lreadline
READLINE_INC	= -I/Users/${USER}/.brew/opt/readline/include

CC				= gcc
# CFLAGS			= -Wall -Wextra -Werror -g
CFLAGS			= -Wall -Wextra -g
# CFLAGS			+= -fsanitize=address
MKDIR			= mkdir -p
RM				= rm -rf

all: ${NAME}

${NAME}: ${OBJS}
	make -C libft
	${CC} -o ${NAME} ${LIBFT} ${READLINE} ${INCLUDE} ${OBJS} ${CFLAGS}

${OUT_DIR}%.o: %.c Makefile
	${MKDIR} ${OUT_DIR}
	${MKDIR} ${@D}
	${CC} ${CFLAGS} ${INCLUDE} ${READLINE_INC} $< -c -o $@

clean:
	make clean -C libft
	${RM} ${OBJS}
	${RM} ${OUT_DIR}

fclean:	clean
	make fclean -C libft
	${RM} ${NAME}

re: fclean ${NAME}

bonus:	all

.PHONY:	all clean fclean re bonus
