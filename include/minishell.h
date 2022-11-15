/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:10:43 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/09 17:21:36 by aho              ###   ########.fr       */
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

/* 0 == str
 * 1 == < 60
 * 2 == > 62
 * 3 == <<
 * 4 == >>
 * 5 == ' 39
 * 6 == " 34
 * 7 == | 124
 * 8 == && (28 &)
 * 9 == ||
 * 10 == * 42
*/

// --------------------------aho------------------------

typedef struct s_quote		t_quote;
typedef struct s_shell		t_shell;
typedef struct s_section	t_section;
typedef struct s_command	t_command;
typedef struct s_tmp		t_tmp;

struct s_quote
{
	int	i;
	int	squote;
	int	dquote;
	int	segment;
	int	chr;
};

//	parsing.c
int		ms_parsing(char *buff);
int		ms_errors(int cmd);
void	ms_quote_checker(const char *buff,const int *j,
						 int *squote1, int *dquote1);

//	syntax.c
int		ms_not_covered(const char *buff);

//	section_creation, section.c
t_section	*ms_section(char *buff);
int			ms_nbr_section(const char *buff);
void		ms_word(const char *buff, t_section *section);
void		ms_word_copy(char *buff, t_section *section);
void		ms_field(t_section *section, int nbr);

//	ms_list.c
int			ms_new(t_tmp **tmp, int field, char *str);

//	ms_tmp.c
t_tmp	*ms_tmp(char *str);
int		ms_check_buffer(const char *str, int index);

// ms_buffer.c
int		ms_qbuffer(t_tmp **tmp, int index, int field_buff,const char *str);
int		ms_sbuffer(t_tmp **tmp, int index, int field_buff,const char *str);
int		ms_obuffer(t_tmp **tmp, int index, int field_buff, const char *str);

// ms_ibuffer.c
int		ms_ibuffer(t_tmp **tmp, int index, int field_buff, const char *str);

// --------------------------aho------------------------

struct s_tmp
{
	int		field;
	char	*str;
	t_tmp	*next;
};

struct s_section
{
	int					field;
	char				*section;
	t_tmp				*tmp;
	struct s_command	*cmd;
};

struct	s_shell
{
	struct	termios	termios_config;
	struct	termios	backup;
	char			**env;
};

struct	s_command
{
	char	*name;
	char	**args;
	int		in_fd;
	int		err_fd;
	int		out_fd;
	struct s_command	*next;
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

//	shell_init.c
t_shell			shell_init(char **env);
void			shell_restore(t_shell *shell);

//	signal.c
void			signal_setup(void);
void			signal_setup_fork(void);

#endif
