/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:10:43 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/21 12:55:01 by gbaumgar         ###   ########.fr       */
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
# include "ms_fd_manager.h"

# define SHELL_NAME "minishell"

extern int					g_exit_code;

typedef struct s_shell		t_shell;
typedef struct s_section	t_section;
typedef struct s_command	t_command;
typedef struct s_pipe		t_pipe;
typedef void				(*t_builtins)(t_command *, char ***);

struct	s_shell
{
	struct termios		termios_config;
	struct termios		termios_backup;
	struct sigaction	signal_backup;
	char				**env;
	int					stdin_backup;
	int					stdout_backup;
};

struct s_pipe
{
	int	prev_r;
	int	prev_w;
	int	cur_r;
	int	cur_w;
};

//	builtins/ms_cd.c
void			ms_cd(t_command *cmd, char ***env);

//	builtins/ms_echo.c
void			ms_echo(t_command *cmd, char ***env);

//	builtins/ms_exit.c
void			ms_exit(t_command *cmd, char ***env);

//	builtins/ms_export.c
void			ms_export(t_command *cmd, char ***env);
void			ms_export_print(char **env, int status);

//	builtins/ms_export_utils.c
int				ms_export_delim(char *s);
int				ms_export_exists(char *s, char **env);
char			*ms_export_get_value(char *s, char **env);
void			ms_export_destroy(char **env);

//	builtins/ms_pwd.c
void			ms_pwd(t_command *cmd, char ***env);

//	builtins/ms_unset.c
void			ms_unset(t_command *cmd, char ***env);

//	ms_cmd_manager.c
int				ms_command_manager(t_section *section, t_shell *shell);

//	ms_error.c
int				ms_error(const char *str);

//	ms_shell_init.c
t_shell			shell_init(int argc, char **argv, char **env);
void			shell_restore(t_shell *shell);

//	ms_signal.c
void			signal_setup(t_shell *shell);
void			signal_restore(t_shell *shell);

//DEBUG
void			ms_debug_print_section(t_section *section);
void			ms_debug_print_fdlst(t_fdlst *fdlst);
//DEBUG

#endif
