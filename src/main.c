/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:09:44 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/24 12:47:46 by gbaumgar         ###   ########.fr       */
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

void	ms_buffer_handler(char *buf, t_shell *shell)
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
			ms_command_manager(section, shell);
			printf("3 -> %d\n", g_exit_code);
		}
		ms_fd_close(section->fdlst, shell);
		printf("4 -> %d\n", g_exit_code);
		ms_section_destroy(section);
		printf("5 -> %d\n", g_exit_code);
	}
	free(buf);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;	
	char		*buf;

	shell = ms_shell_init(argc, argv, envp);
	while (1)
	{
		ms_signal_setup(&shell);
		while (waitpid(0, 0, 0) != -1)
			;
		buf = readline(SHELL_NAME "> ");
		ms_signal_restore(&shell);
		if (!buf)
		{
			ft_putstr_fd("\033[A", 1);
			ft_putstr_fd("minishell> exit\n", 1);
			break ;
		}
		else
			ms_buffer_handler(buf, &shell);
	}
	ms_shell_restore(&shell);
	return (0);
}
