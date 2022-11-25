/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:28:22 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/25 11:17:10 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_signal_readline(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	ms_signal_fork(int signum)
{	
	int	i;

	if (signum == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
	else if (signum == SIGQUIT)
	{
		write(STDOUT_FILENO, "Quit: 3\n", 8);
		i = -1;
		while (g_g.pid[++i] != 0)
			kill(g_g.pid[i], SIGINT);
	}
}

static void	ms_signal_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		close(STDIN_FILENO);
		g_g.exitcode = -1;
	}
	else if (signum == SIGQUIT)
		return ;
}

void	ms_signal_setup(int status)
{
	if (status == 0)
	{
		signal(SIGINT, ms_signal_readline);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (status == 1)
	{
		signal(SIGINT, ms_signal_fork);
		signal(SIGQUIT, ms_signal_fork);
	}
	else if (status == 2)
	{
		signal(SIGINT, ms_signal_heredoc);
		signal(SIGQUIT, ms_signal_heredoc);
	}
}
