/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:15:29 by aho               #+#    #+#             */
/*   Updated: 2022/11/21 14:35:23 by gbaumgar         ###   ########.fr       */
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

struct s_quote
{
	int	i;
	int	squote;
	int	dquote;
	int	segment;
	int	chr;
};

struct s_tmp
{
	int		field;
	char	*str;
	char	*entry;
	t_tmp	*next;
};

struct	s_command
{
	char				*name;
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

//	parsing.c
t_section	*ms_parsing(char *buff);
int			ms_errors(int cmd);
void		ms_quote_checker(const char *buff, const int *j, \
	int *squote1, int *dquote1);

//	syntax.c
int			ms_syntax_error(char const *buff);
int			ms_not_covered(const char *buff);

//	section_creation, section.c
t_section	*ms_section(char *buff, t_fdlst *fdlst);
int			ms_nbr_section(const char *buff);
void		ms_word(const char *buff, t_section *section);
void		ms_word_copy(char *buff, t_section *section);
void		ms_field(t_section *section, int nbr);

//	ms_list.c - ms_list2.c
int			ms_new(t_tmp **tmp, int field, char *str);
t_fdlst		*ms_new_fdlst(int field, char *str);
void		ms_fdlstadd_back(t_fdlst **lst, t_fdlst *new);
int			ms_new3(t_tmp **tmp, int field, char *str, char *entry);

//	ms_tmp.c
t_tmp		*ms_tmp(char *str);
int			ms_check_buffer(const char *str, int index);

// ms_buffer.c
int			ms_expend_length(const char *str, int index);
int			ms_expend_index(const char *str, int index);
void		ms_expend_copy(char *cpy, int *i, const char *str, int *end);

int			ms_qbuffer(t_tmp **tmp, int index, int field_buff, const char *str);
int			ms_sbuffer(t_tmp **tmp, int index, int field_buff, const char *str);
int			ms_obuffer(t_tmp **tmp, int index, int field_buff, const char *str);
int			ms_ibuffer(t_tmp **tmp, int index, int field_buff, const char *str);

// ms_result.c
t_command	*ms_result(t_tmp *tmp, t_fdlst **fdlst);

// ms_print_pars.c
void		ms_print_section(t_section *section);
void		ms_print_pars(t_section *section);

// ms_fdlst.c
void	ms_result_fdlst(t_tmp *tmp, t_fdlst **unknow);

#endif
