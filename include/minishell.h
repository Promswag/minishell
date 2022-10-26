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


typedef struct s_pars
{
	int i;
	int squote;
	int dquote;
}	t_pars;

typedef struct s_shell
{
	struct termios	termios_config;
	struct termios	backup;

}	t_shell;

typedef struct s_command
{
	char	*fonction;
	int		fd_in;
	char	*arg;
	int		fd_out;
}	t_command;

typedef struct s_tree
{
	int 	num_cmd;
	int 	stdin_bool;
	char 	**
}	t_tree;

// Parsing_syntaxe

t_command	*ms_parsing(char *buff);
int			ms_errors(int cmd);
int			ms_syntaxe(char *buff);

//	signal.c
void		signal_setup(void);

//	shell_init.c
t_shell		shell_init(void);
void		shell_restore(t_shell *shell);

#endif