/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:10:43 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/25 17:51:56 by gbaumgar         ###   ########.fr       */
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
# include <signal.h>
# include "parser.h"
# include "ms_fd_manager.h"

# define SHELL_NAME "minishell"
# define MAX_FORK 64

extern struct s_g			g_g;

typedef struct s_g			t_g;
typedef struct s_shell		t_shell;
typedef struct s_section	t_section;
typedef struct s_command	t_command;
typedef struct s_pipe		t_pipe;
typedef void				(*t_builtins)(t_command *, char ***);

struct	s_g
{
	int		exitcode;
	int		pid[MAX_FORK];
	int		status;
};

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

//	main.c
void			ms_section_destroy(t_section *section);

//	builtins/ms_cd.c
void			ms_cd(t_command *cmd, char ***env);

//	builtins/ms_echo.c
void			ms_echo(t_command *cmd, char ***env);

//	builtins/ms_exit.c
void			ms_exit(t_section *section, t_shell *shell);

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
int				ms_cmd_is_builtins(t_command *cmd);

//	ms_cmd_manager_utils.c
void			ms_cmd_setup_fd(t_section *section, t_pipe pfd);

//	ms_error.c
int				ms_error(const char *str);
int				ms_error_s(const char *s1, const char *s2);

//	ms_shell_init.c
t_shell			ms_shell_init(int argc, char **argv, char **env);
void			ms_shell_reset(t_shell *shell);
void			ms_shell_state(t_shell *shell, int state);
void			ms_shell_restore(t_shell *shell);

//	ms_signal.c
void			ms_signal_setup(int status);

#endif
