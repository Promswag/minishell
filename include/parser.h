/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:15:29 by aho               #+#    #+#             */
/*   Updated: 2022/11/23 16:13:30 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../libft/include/libft.h"
# include "minishell.h"
# include <termios.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "ms_fd_manager.h"

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
 * 11 == $ 36
 * 12 == heredoc quoted;
*/

typedef struct s_quote		t_quote;
typedef struct s_section	t_section;
typedef struct s_command	t_command;
typedef struct s_tmp		t_tmp;
typedef struct s_ebuffer	t_ebuffer;

struct s_ebuffer
{
	int	x;
	int	y;
	int	*trigger;
};

struct s_quote
{
	int	i;
	int	squote;
	int	dquote;
	int	segment;
	int	chr;
	int	*trigger;
};

struct s_tmp
{
	int		field;
	char	*str;
	t_tmp	*next;
};

struct	s_command
{
	char				*path;
	char				**args;
	struct s_fdlst		*fd_in;
	struct s_fdlst		*fd_out;
};

struct s_section
{
	int					field;
	char				*section;
	struct s_fdlst		*fdlst;
	struct s_command	*cmd;
};

//	pars/parsing.c
t_section	*ms_parsing(char *buff, char **env);
int			ms_errors(int cmd);
void		ms_quote_checker(const char *buff, const int *j, \
	int *squote1, int *dquote1);

//	pars/syntax.c
int			ms_syntax_error(char const *buff);
int			ms_not_covered(const char *buff);

//	pars/section.c
t_section	*ms_section(char *buff);
int			ms_nbr_section(const char *buff);
void		ms_word(const char *buff, t_section *section);
void		ms_word_copy(char *buff, t_section *section);
void		ms_field(t_section *section, int nbr);

//	pars/ms_list.c
int			ms_new(t_tmp **tmp, int field, char *str);

//	pars/ms_list2.c
t_fdlst		*ms_new_fdlst(int field, char *str);
void		ms_fdlstadd_back(t_fdlst **lst, t_fdlst *new);

//	pars/ms_tmp.c
t_tmp		*ms_tmp(char *str, char **env, int *trigger);
int			ms_check_buffer(const char *str, int index);

//	pars/ms_buffer.c
int			ms_expend_index(const char *str, int index);
int			ms_line_too_long(const char *str, t_quote quote);
void		ms_expend_copy(\
	char *cpy, t_ebuffer *expend, const char *str, char **env);
int			ms_expend_length(const char *str, int index, char **env, t_quote *quote);

//	pars/ms_sbuffer.c
int			ms_sbuffer(\
	t_tmp **tmp, t_ebuffer ebuffer, const char *str, char **env);

//	pars/ms_qbuffer.c
int			ms_qbuffer(\
	t_tmp **tmp, t_ebuffer ebuffer, const char *str, char **env);

//	pars/ms_ibuffer.c
int			ms_ibuffer(\
	t_tmp **tmp, t_ebuffer ebuffer, const char *str, char **env);

//	pars/ms_obuffer.c
int			ms_obuffer(\
	t_tmp **tmp, t_ebuffer ebuffer, const char *str, char **env);

//	pars/ms_result.c
t_command	*ms_result(t_tmp *tmp, t_fdlst **fdlst, char **env);

//	pars/ms_path_finder.c
char		*ms_path_finder(char *name, char **env);

//	pars/ms_syntax_utils.c
int			ms_newline_errors_in(char const *buff, int index, char chr);
int			ms_special_token_in(char const *buff, int index, char chr);

#endif
