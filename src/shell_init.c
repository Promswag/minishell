/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:34:55 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/14 18:44:34 by gbaumgar         ###   ########.fr       */
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
	tcsetattr(STDIN_FILENO, TCSANOW, &shell->backup);
}

t_shell	shell_init(int argc, char **argv, char **env)
{
	t_shell	shell;

	if (argc != 1)
	{
		write(2, SHELL_NAME, ft_strlen(SHELL_NAME));
		write(2, " does not take arguments\n", 25);
		exit(1);
	}
	shell_env(&shell, env);
	tcgetattr(STDIN_FILENO, &shell.backup);
	tcgetattr(STDIN_FILENO, &shell.termios_config);
	shell.termios_config.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &shell.termios_config);
	return (shell);
}
