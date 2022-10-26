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

typedef struct s_command
{
	char				*command;
	char				**args;
	char				*stdout;
	int					fd;
	struct s_command	*next;
}	t_command;

//	signal.c
void		signal_setup(void);

//	shell_init.c
t_shell		shell_init(void);
void		shell_restore(t_shell *shell);

#endif