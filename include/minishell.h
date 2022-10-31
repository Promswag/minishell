/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:10:43 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/10/31 12:12:17 by gbaumgar         ###   ########.fr       */
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
	int	i;
	int	squote;
	int	dquote;
}	t_pars;

typedef struct s_shell
{
	struct termios	termios_config;
	struct termios	backup;
	char			**env;

}	t_shell;

typedef struct s_command
{
	char				*name;
	char				**args;
	char				*stdout;
	int					fd;
	struct s_command	*next;
}	t_command;

//	builtins/ms_echo.c
int				ms_echo(t_command cmd);

//	builtins/ms_export.c
int				ms_export(t_command cmd, char ***env);

//	pars/ms_errors.c
int				ms_errors(int cmd);

//	pars/ms_parsing.c
t_command		ms_parsing(char *buff);

//	pars/ms_syntax.c
int				ms_syntaxe(char *buff);

//	shell_init.c
t_shell			shell_init(char **env);
void			shell_restore(t_shell *shell);

//	signal.c
void			signal_setup(void);
void			signal_setup_fork(void);

#endif