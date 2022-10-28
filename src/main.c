/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:09:44 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/10/28 17:05:39 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int			i;
	pid_t		pid;
	t_shell		shell;	
	char		*buf;
	int			stat_loc;
	t_command	cmd;
	(void)argc;
	(void)argv;

	cmd.args = 0;
	cmd.fd = 1;
	i = 0;
	shell = shell_init();
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
		// ms_echo(cmd);
		ms_export(cmd, envp);

		// while(*envp)
		// 	printf("%s\n", *envp++);

		// signal_setup_fork();
		// if (i++ == 0)
		// 	pid = fork();
		// if (pid == 0)
		// {
		// 	execve("/bin/cat", NULL, NULL);
		// 	exit(0);
		// }
		// else if (i == 1)
		// {
		// 	waitpid(pid, &stat_loc, 0);
		// 	printf("%d\n", WEXITSTATUS(stat_loc));
		// 	pid = 1;
		// 	i = 0;
		// }
	}
	shell_restore(&shell);
	return (0);
}
