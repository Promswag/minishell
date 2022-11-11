/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:10:43 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/11 17:54:18 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include "minishell.h"
# include <termios.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

# define SHELL_NAME "minishell"

typedef struct s_quote		t_quote;
typedef struct s_shell		t_shell;
typedef struct s_section	t_section;
typedef struct s_command	t_command;
typedef struct s_pipe		t_pipe;

struct s_quote
{
	int	i;
	int	squote;
	int	dquote;
};

struct s_shell
{
	struct termios	termios_config;
	struct termios	backup;
	char			**env;
};

struct s_section
{
	int					field;
	char				*section;
	struct s_command	*cmd;
};

struct s_command
{
	char				*name;
	char				**args;
	int					in_fd;
	int					out_fd;
	int					err_fd;
	struct s_command	*next;
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
int				ll_overflow_check(const char *str);
int				ms_exit(t_command cmd, char ***env);

//	builtins/ms_export.c
int				ms_export(t_command cmd, char ***env);
void			ms_export_print(int fd, char **env, int status);
void			ms_export_destroy(char **env);
char			*ms_export_get_value(char *s, char **env);

//	builtins/ms_pwd.c
int				ms_pwd(t_command cmd, char ***env);

//	builtins/ms_unset.c
int				ms_unset(t_command cmd, char ***env);

//	pars/ms_errors.c
int				ms_errors(int cmd);

//	pars/ms_parsing.c
int				ms_parsing(char *buff);
int				ms_errors(int cmd);
int				ms_not_covered(char *buff);

//	pars/ms_syntax.c
int				ms_syntaxe(char *buff);

//	cmd_manager.c
int				ms_command_manager(t_section *section, t_shell *shell);

//	shell_init.c
t_shell			shell_init(char **env);
void			shell_restore(t_shell *shell);

//	signal.c
void			signal_setup(void);
void			signal_setup_fork(void);

#endif