/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:28:22 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/21 10:27:28 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

static void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
	{
		rl_redisplay();
	}
}

static void	signal_handler_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		write(STDIN_FILENO, "\n", 1);
		close(STDIN_FILENO);
	}
	if (signum == SIGQUIT)
		return ;
}

void	signal_setup(t_shell *shell)
{
	struct sigaction	sa;

	sa.sa_handler = &signal_handler;
	sigaction(SIGINT, &sa, &shell->signal_backup);
	sigaction(SIGQUIT, &sa, &shell->signal_backup);
}

void	signal_restore(t_shell *shell)
{
	(void)shell;
	signal(SIGINT, &signal_handler_heredoc);
	signal(SIGQUIT, &signal_handler_heredoc);
	// sigaction(SIGINT, &shell->signal_backup, NULL);
	// sigaction(SIGQUIT, &shell->signal_backup, NULL);
}
