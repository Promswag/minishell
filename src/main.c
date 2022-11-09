/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:09:44 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/09 11:15:14 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;	
	char		*buf;

	(void)argc;
	(void)argv;
	shell = shell_init(envp);
	while (1)
	{
		signal_setup();
		buf = readline("minishell> ");
		if (!buf)
		{
			ft_putstr_fd("\033[A", 1);
			ft_putstr_fd("minishell> exit\n", 1);
			break ;
		}
		else
		{
			ft_putstr_fd(buf, 1);
			if (*buf != 0)
				write(1, "\n", 1);
		}
	}
	shell_restore(&shell);
	return (0);
}
