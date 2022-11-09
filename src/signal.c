/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:28:22 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/10/28 15:05:41 by gbaumgar         ###   ########.fr       */
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

static void	signal_handler_fork(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
	}
	if (signum == SIGQUIT)
	{
		write(1, "Quit: 3\n", 8);
	}
}

void	signal_setup(void)
{
	signal(SIGINT, &signal_handler);
	signal(SIGQUIT, &signal_handler);
}

void	signal_setup_fork(void)
{
	signal(SIGINT, &signal_handler_fork);
	signal(SIGQUIT, &signal_handler_fork);
}
