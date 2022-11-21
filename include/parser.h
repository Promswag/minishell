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
 * 12 ==
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
	char	*name;
	char	**args;
	t_fdlst		*fd_in; //je l'ai mis la parce qu'au fond, il fais la meme chose que les trois du bas
	t_fdlst		*fd_out;
//	int		in_fd; //fais ce que tu veut avec
//	int		err_fd; //idem
//	int		out_fd; //idem x3
	struct s_command	*next; //inutile car la prochaine commande = prochaine section.
};

struct s_section
{
	int			field;
	char		*section;
	t_command	cmd;
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

//	ms_list.c - ms_list2.c
int			ms_new(t_tmp **tmp, int field, char *str);
int			ms_new2(t_fdlst **unknow, int field, char *str, char *entry);
int			ms_new3(t_tmp **tmp, int field, char *str, char *entry);

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

// ms_result.c
t_command	ms_result(t_tmp *tmp);

// ms_print_pars.c
void	ms_print_section(t_section *section);
void	ms_print_pars(t_section *section);

#endif
