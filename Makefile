# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/21 12:09:04 by gbaumgar          #+#    #+#              #
#    Updated: 2022/11/09 18:06:41 by aho              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

USER			= aho

NAME			= minishell
INC_DIR			= ./include/
SRC_DIR			= ./src/
OUT_DIR			= ./obj/

SRC				= 	shell_init.c \
					signal.c \
					cmd_manager.c \
					builtins/ms_cd.c \
					builtins/ms_echo.c \
					builtins/ms_exit.c \
					builtins/ms_export.c \
					builtins/ms_unset.c \
					builtins/ms_pwd.c \
					pars/ms_errors.c \
					pars/ms_parsing.c \
					pars/ms_syntax.c \
					pars/ms_section.c \

SRC 			+=	main.c
# SRC 			+=	test.c \
					# main_local.c

SRCC			= ${addprefix ${SRC_DIR}, ${SRC}}
OBJS			= ${SRCC:%.c=${OUT_DIR}%.o}

INCLUDE			= -I${INC_DIR}
LIBFT			= -Llibft -lft
READLINE		= -L/Users/${USER}/.brew/opt/readline/lib -lreadline
READLINE_INC	= -I/Users/${USER}/.brew/opt/readline/include

CC				= gcc
CFLAGS			= -g -Wall -Wextra
CFLAGS			+= -Werror
CFLAGS			+= -fsanitize=address
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
