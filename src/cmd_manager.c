/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:37:42 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/10 18:40:45 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef int	(*t_builtins)(t_command, char ***);
int			ms_command_manager(t_section *section, t_shell *shell);
static int	ms_cmd_exec(t_command cmd, t_shell *shell);
static int	ms_cmd_is_builtins(t_command cmd);
static int	ms_cmd_exec_builtins(t_command cmd, t_shell *shell, int index);

int	ms_command_manager(t_section *section, t_shell *shell)
{
	long	pipefd_cur;
	long	pipefd_prev;

	pipefd_prev = -1;
	while ((*section).field != -1)
	{
		// if ((section + 1)->field == 1)
			// pipe(&pipefd_cur);
			// if ((section + 1)->field != 1)
			// 	close(pipefd_cur >> (sizeof(pipefd_cur) << 2));
			// if ((*section).cmd->out_fd == 1 && (section + 1)->field == 1)
			// 	dup2(pipefd_cur >> (sizeof(pipefd_cur) << 2), STDOUT_FILENO);
			// else
			// 	dup2((*section).cmd->out_fd, STDOUT_FILENO);
			// if (pipefd_prev != -1)
			// {
			// 	if ((*section).cmd->in_fd == 0)
			// 		dup2(pipefd_cur, STDIN_FILENO);
			// 	else
			// 		dup2((*section).cmd->in_fd, STDIN_FILENO);
			// }
			// else
			// 	close(pipefd_cur);
			// ms_cmd_exec(*section->cmd, shell);
			// pipe(&pipefd_prev);
			// if ((section + 1)->field == 1)
			// 	section++;
		// else
		// {
		// }
		// section++;
		dup2(1, 1);
		ms_cmd_exec(*section->cmd, shell);
		section++;
	}
	return (0);
}

static int	ms_cmd_exec(t_command cmd, t_shell *shell)
{
	pid_t	pid;
	int		builtins;

	builtins = ms_cmd_is_builtins(cmd);
	if (builtins == 0)
		ms_exit(cmd, &shell->env);
	pid = fork();
	if (!pid)
	{
		if (builtins != -1)
			ms_cmd_exec_builtins(cmd, shell, builtins);
		else
			execve("/bin/ls", (char *[]){"ls", "-la", "obj", 0}, shell->env);
	}

}

static int	ms_cmd_is_builtins(t_command cmd)
{
	static char	*builtins[] = \
		{"exit",
		"pwd",
		"cd",
		"echo",
		"export",
		"unset",
		0};
	int			i;

	i = -1;
	while (builtins[++i])
		if (!ft_strncmp(cmd.name, builtins[i], ft_strlen(builtins[i]) + 1))
			return (i);
	return (-1);
}

static int	ms_cmd_exec_builtins(t_command cmd, t_shell *shell, int index)
{
	static t_builtins	builtins[] = \
		{ms_exit, ms_pwd, ms_cd, ms_echo, ms_export, ms_unset};

	builtins[index](cmd, &shell->env);
	return (0);
}
