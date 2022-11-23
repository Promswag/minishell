/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_shell_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:34:55 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/22 13:08:43 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	shell_env(t_shell *shell, char **env)
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

void	shell_restore(t_shell *shell)
{
	int	i;

	i = -1;
	tcsetattr(STDIN_FILENO, TCSANOW, &shell->termios_backup);
	if (shell->env)
	{
		while (shell->env && shell->env[++i])
			free(shell->env[i]);
		free(shell->env);
	}
}

t_shell	shell_init(int argc, char **argv, char **env)
{
	t_shell	shell;

	(void)argv;
	if (argc != 1)
	{
		write(STDERR_FILENO, SHELL_NAME, ft_strlen(SHELL_NAME));
		write(STDERR_FILENO, " does not take arguments\n", 25);
		exit(EXIT_FAILURE);
	}
	shell.stdin_backup = dup(STDIN_FILENO);
	shell.stdout_backup = dup(STDOUT_FILENO);
	shell_env(&shell, env);
	tcgetattr(STDIN_FILENO, &shell.termios_backup);
	tcgetattr(STDIN_FILENO, &shell.termios_config);
	shell.termios_config.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &shell.termios_config);
	return (shell);
}
