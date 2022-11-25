/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_shell_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:34:55 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/25 12:31:10 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_shell_env(t_shell *shell, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	shell->env = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (env[++i])
		shell->env[i] = ft_strdup(env[i]);
	shell->env[i] = 0;
}

void	ms_shell_reset(t_shell *shell)
{
	int	i;

	dup2(shell->stdin_backup, STDIN_FILENO);
	dup2(shell->stdout_backup, STDOUT_FILENO);
	i = -1;
	while (++i < MAX_FORK)
		g_g.pid[i] = 0;
}

void	ms_shell_restore(t_shell *shell)
{
	int	i;

	i = -1;
	tcsetattr(STDIN_FILENO, TCSANOW, &shell->termios_backup);
	close(shell->stdin_backup);
	close(shell->stdout_backup);
	if (shell->env)
	{
		while (shell->env && shell->env[++i])
			free(shell->env[i]);
		free(shell->env);
	}
	sigaction(SIGINT, &shell->signal_backup, NULL);
	sigaction(SIGQUIT, &shell->signal_backup, NULL);
	rl_clear_history();
}

t_shell	ms_shell_init(int argc, char **argv, char **env)
{
	t_shell	shell;

	(void)argv;
	if (argc != 1)
	{
		write(STDERR_FILENO, SHELL_NAME, ft_strlen(SHELL_NAME));
		write(STDERR_FILENO, " does not take arguments\n", 25);
		exit(EXIT_FAILURE);
	}
	sigaction(SIGINT, NULL, &shell.signal_backup);
	sigaction(SIGQUIT, NULL, &shell.signal_backup);
	shell.stdin_backup = dup(STDIN_FILENO);
	shell.stdout_backup = dup(STDOUT_FILENO);
	tcgetattr(STDIN_FILENO, &shell.termios_backup);
	tcgetattr(STDIN_FILENO, &shell.termios_config);
	shell.termios_config.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &shell.termios_config);
	ms_shell_env(&shell, env);
	return (shell);
}
