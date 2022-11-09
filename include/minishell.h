/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:10:43 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/10/26 14:47:09 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include "minishell.h"
# include <termios.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_shell
{
	struct termios	termios_config;
	struct termios	backup;

}	t_shell;

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

typedef struct s_quote
{
	int	i;
	int	squote;
	int	dquote;
	int	segment;
	int	chr;
}	t_quote;

typedef struct s_section
{
	int		field;
	char	*section;
}	t_section;

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

// --------------------------aho------------------------

//	signal.c
void		signal_setup(void);

//	shell_init.c
t_shell		shell_init(void);
void		shell_restore(t_shell *shell);

#endif