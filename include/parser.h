/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aho <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:15:29 by aho               #+#    #+#             */
/*   Updated: 2022/11/16 13:15:30 by aho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSEUR_H
# define PARSEUR_H

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
 * 11 == $ 36
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
	t_tmp	*next;
};

struct s_section
{
	int					field;
	char				*section;
	t_tmp				*tmp;
	struct s_command	*cmd;
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
int		ms_expend_length(const char *str, int index);
int		ms_expend_index(const char *str, int index);
void	ms_expend_copy(char *cpy, int *i, const char *str, int *end);


int		ms_qbuffer(t_tmp **tmp, int index, int field_buff,const char *str);
int		ms_sbuffer(t_tmp **tmp, int index, int field_buff,const char *str);
int		ms_obuffer(t_tmp **tmp, int index, int field_buff, const char *str);
int		ms_ibuffer(t_tmp **tmp, int index, int field_buff, const char *str);

#endif
