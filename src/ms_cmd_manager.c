/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:37:42 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/24 18:44:57 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ms_command_manager(t_section *section, t_shell *shell);
static void	ms_cmd_exec(t_section *section, t_shell *shell, t_pipe pfd);
int			ms_cmd_is_builtins(t_command *cmd);
static void	ms_cmd_exec_builtins(t_section *sec, t_shell *shell, int index);
static int	ms_cmd_fork(int *pid, t_section *sec, t_shell *shell, t_pipe pfd);

int	ms_command_manager(t_section *section, t_shell *shell)
{
	t_pipe		pfd;
	pid_t		pid;
	int			status;

	status = 0;
	pid = 0;
	pfd = (t_pipe){-1, -1, -1, -1};
	while (section && section->section)
	{
		if (section->field == 1 && pipe((int *)&pfd.cur_r) == -1)
			return (ms_error("pipe"));
		if (ms_cmd_is_builtins(section->cmd) != -1)
			ms_cmd_exec(section, shell, pfd);
		else if (ms_cmd_fork(&pid, section, shell, pfd))
			return (ms_error("fork"));
		close(pfd.cur_w);
		close(pfd.prev_r);
		if (section->field == 0)
			close(pfd.cur_r);
		pfd = (t_pipe){.prev_r = pfd.cur_r, .prev_w = pfd.cur_w, -1, -1};
		section++;
	}
	return (pid);
}

static int	ms_cmd_fork(int *pid, t_section *sec, t_shell *shell, t_pipe pfd)
{
	*pid = fork();
	if (*pid == -1)
		return (1);
	if (*pid == 0)
	{
		ms_signal_setup(1);
		ms_cmd_exec(sec, shell, pfd);
	}
	return (0);
}

static void	ms_cmd_exec(t_section *section, t_shell *shell, t_pipe pfd)
{
	int		builtins;

	ms_cmd_setup_fd(section, pfd);
	builtins = ms_cmd_is_builtins(section->cmd);
	if (builtins != -1)
	{
		if (builtins == 0 && pfd.prev_r != -1)
			return ;
		ms_cmd_exec_builtins(section, shell, builtins);
		dup2(shell->stdin_backup, STDIN_FILENO);
		dup2(shell->stdout_backup, STDOUT_FILENO);
	}
	else
	{
		close(pfd.cur_r);
		close(pfd.cur_w);
		close(pfd.prev_r);
		close(pfd.prev_w);
		execve(section->cmd->path, section->cmd->args, shell->env);
		exit(127);
	}
}

int	ms_cmd_is_builtins(t_command *cmd)
{
	static char	*builtins[] = \
		{"exit", "pwd", "cd", "echo", "export", "env", "unset", 0};
	int			i;

	i = -1;
	while (builtins[++i])
		if (cmd->args[0] && \
			!ft_strncmp(cmd->args[0], builtins[i], ft_strlen(builtins[i]) + 1))
			return (i);
	return (-1);
}

static void	ms_cmd_exec_builtins(t_section *sec, t_shell *shell, int index)
{
	static t_builtins	builtins[] = \
		{0, ms_pwd, ms_cd, ms_echo, ms_export, ms_export, ms_unset};

	if (index != 0)
		builtins[index](sec->cmd, &shell->env);
	else
		ms_exit(sec, shell);
}
