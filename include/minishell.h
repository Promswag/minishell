/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:10:43 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/10/25 15:18:10 by gbaumgar         ###   ########.fr       */
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

typedef struct s_command
{
	char				*command;
	char				**args;
	char				*stdout;
	int					fd;
	struct s_command	*next;
}	t_command;

// Parsing_syntaxe

t_command	ms_parsing(char *buff);
int			ms_errors(int cmd);
int			ms_syntaxe(char *buff);

#endif