/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:09:44 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/24 14:56:17 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code;

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
		printf("1 -> %d\n", g_exit_code);
		section = ms_parsing(buf, shell->env);
		printf("2 -> %d\n", g_exit_code);
		if (section && \
			!ms_fd_manager(section->fdlst, shell) && g_exit_code != -1)
		{
			*pid = ms_command_manager(section, shell);
			printf("3 -> %d\n", g_exit_code);
		}
		if (section)
			ms_fd_close(section->fdlst, shell);
		printf("4 -> %d\n", g_exit_code);
		ms_section_destroy(section);
		printf("5 -> %d\n", g_exit_code);
	}
	free(buf);
}

void	ms_stop(t_shell *shell)
{
	ft_putstr_fd("\033[A", 1);
	ft_putstr_fd("minishell> exit\n", 1);
	ms_shell_restore(shell);
	exit(0);
}

void	ms_exit_code_getter(pid_t *pid)
{
	int			status;

	status = 0;
	if (*pid)
	{
		waitpid(*pid, &status, 0);
		g_exit_code = WEXITSTATUS(status);
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
		ms_exit_code_getter(&pid);
		while (waitpid(0, 0, 0) != -1)
			;
		ms_signal_setup(&shell);
		buf = readline(SHELL_NAME "> ");
		ms_signal_restore(&shell);
		if (!buf)
			ms_stop(&shell);
		else
			ms_buffer_handler(&pid, buf, &shell);
	}
	ms_shell_restore(&shell);
	return (0);
}
