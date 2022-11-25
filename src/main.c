/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:09:44 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/25 17:54:39 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_g	g_g;

void	ms_section_destroy(t_section *section)
{
	t_section	*tmp;
	int			i;

	tmp = section;
	while (section && (*section).section)
	{
		free((*section).section);
		if ((*section).cmd)
		{
			if ((*section).cmd->path)
				free((*section).cmd->path);
			i = -1;
			while ((*section).cmd->args && (*section).cmd->args[++i])
				free((*section).cmd->args[i]);
			if ((*section).cmd->args)
				free((*section).cmd->args);
			*(*section).cmd = (t_command){0, 0, 0, 0};
			free((*section).cmd);
		}
		*section = (t_section){0, 0, 0, 0};
		section++;
	}
	if (tmp)
		free(tmp);
}

void	ms_buffer_handler(pid_t *pid, char *buf, t_shell *shell)
{
	t_section	*section;

	if (*buf)
	{
		add_history(buf);
		section = ms_parsing(buf, shell->env);
		if (section && \
			!ms_fd_manager(section->fdlst, shell) && g_g.exitcode != -1)
		{
			*pid = ms_command_manager(section, shell);
		}
		if (section)
			ms_fd_close(section->fdlst);
		ms_section_destroy(section);
	}
	free(buf);
}

void	ms_stop(t_shell *shell)
{
	write(STDOUT_FILENO, "\033[A", ft_strlen("\033[A"));
	write(STDOUT_FILENO, SHELL_NAME, ft_strlen(SHELL_NAME));
	write(STDOUT_FILENO, "> exit\n", 7);
	ms_shell_restore(shell);
	exit(127);
}

void	ms_exit_code_getter(pid_t *pid)
{
	int			status;

	status = 0;
	if (*pid)
	{
		waitpid(*pid, &status, 0);
		if (WIFSIGNALED(status))
			g_g.exitcode = 128 + WTERMSIG(status);
		else
			g_g.exitcode = WEXITSTATUS(status);
		*pid = 0;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;	
	char		*buf;
	pid_t		pid;

	shell = ms_shell_init(argc, argv, envp);
	pid = 0;
	while (1)
	{
		ms_signal_setup(1);
		ms_exit_code_getter(&pid);
		ms_shell_state(&shell, 1);
		while (waitpid(0, 0, 0) != -1)
			;
		g_g.status = 0;
		ms_signal_setup(0);
		buf = readline(SHELL_NAME "> ");
		if (!buf)
			ms_stop(&shell);
		else
			ms_buffer_handler(&pid, buf, &shell);
	}
}
