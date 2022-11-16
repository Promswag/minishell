/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:09:44 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/16 17:44:35 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code;

int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;	
	char		*buf;

	shell = shell_init(argc, argv, envp);
	while (1)
	{
		signal_setup();
		while (waitpid(0, 0, 0) != -1)
			;
		buf = readline(SHELL_NAME "> ");
		if (!buf)
		{
			ft_putstr_fd("\033[A", 1);
			ft_putstr_fd("minishell> exit\n", 1);
			break ;
		}
		else
		{
			if (*buf)
			{
				add_history(buf);
				/* PARSE COME HERE */
				ms_command_manager((t_section []){(t_section){0, 0, 0}}, &shell);
			}
		}
	}
	shell_restore(&shell);
	return (0);
}
