/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:10:43 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/16 17:58:50 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"            
# include <termios.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "parser.h"

# define SHELL_NAME "minishell"

extern int g_exit_code;

typedef struct s_shell		t_shell;
typedef struct s_section	t_section;
typedef struct s_command	t_command;
typedef struct s_pipe		t_pipe;
typedef int					(*t_builtins)(t_command, char ***);

struct	s_shell
{
	struct	termios	termios_config;
	struct	termios	backup;
	char			**env;
};

struct s_pipe
{
	int	prev_r;
	int	prev_w;
	int	cur_r;
	int	cur_w;
};

//	builtins/ms_cd.c
int				ms_cd(t_command cmd, char ***env);

//	builtins/ms_echo.c
int				ms_echo(t_command cmd, char ***env);

//	builtins/ms_exit.c
void			ms_exit(t_command cmd, char ***env);

//	builtins/ms_export.c
int				ms_export(t_command cmd, char ***env);
void			ms_export_print(int fd, char **env, int status);
void			ms_export_destroy(char **env);
char			*ms_export_get_value(char *s, char **env);

//	builtins/ms_pwd.c
int				ms_pwd(t_command cmd, char ***env);

//	builtins/ms_unset.c
int				ms_unset(t_command cmd, char ***env);

//	cmd_manager.c
int				ms_command_manager(t_section *section, t_shell *shell);

//	shell_init.c
t_shell			shell_init(int argc, char **argv, char **env);
void			shell_restore(t_shell *shell);

//	signal.c
void			signal_setup(void);
void			signal_setup_fork(void);

#endif
