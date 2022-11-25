# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/21 12:09:04 by gbaumgar          #+#    #+#              #
#    Updated: 2022/11/25 14:57:57 by gbaumgar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell
INC_DIR			= ./include/
SRC_DIR			= ./src/
OUT_DIR			= ./obj/

SRC				= 	main.c \
					ms_error.c \
					ms_shell_init.c \
					ms_signal.c \
					ms_cmd_manager.c \
					ms_cmd_manager_utils.c \
					ms_fd_manager.c \
					ms_heredoc.c \
					ms_heredoc_utils.c \
					builtins/ms_cd.c \
					builtins/ms_echo.c \
					builtins/ms_exit.c \
					builtins/ms_export.c \
					builtins/ms_export_utils.c \
					builtins/ms_unset.c \
					builtins/ms_pwd.c \
					pars/ms_errors.c \
					pars/ms_parsing.c \
					pars/ms_path_finder.c \
					pars/ms_syntax.c \
					pars/ms_section.c \
					pars/ms_tmp.c \
					pars/ms_list.c \
					pars/ms_buffer.c \
					pars/ms_ibuffer.c \
					pars/ms_obuffer.c \
					pars/ms_qbuffer.c \
					pars/ms_sbuffer.c \
					pars/ms_result.c \
					pars/ms_list2.c \
					pars/ms_syntax_utils.c \

SRCC			= ${addprefix ${SRC_DIR}, ${SRC}}
OBJS			= ${SRCC:%.c=${OUT_DIR}%.o}

INCLUDE			= -I${INC_DIR}
LIBFT			= -Llibft -lft
READLINE		= -L/Users/${USER}/.brew/opt/readline/lib -lreadline
READLINE_INC	= -I/Users/${USER}/.brew/opt/readline/include

CC				= gcc
CFLAGS			= -g -Wall -Wextra
CFLAGS			+= -Werror
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
