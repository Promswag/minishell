/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:37:42 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/21 12:43:07 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ms_command_manager(t_section *section, t_shell *shell);
static void	ms_cmd_exec(t_section *section, t_shell *shell, t_pipe pfd);
static int	ms_cmd_is_builtins(t_command *cmd);
static void	ms_cmd_exec_builtins(t_command *cmd, t_shell *shell, int index);
static int	ms_cmd_error(const char *str);

int	ms_command_manager(t_section *section, t_shell *shell)
{
	t_pipe		pfd;
	pid_t		pid;

	pfd = (t_pipe){-1, -1, -1, -1};
	while (section && section->section)
	{
		if (ms_cmd_is_builtins(section->cmd) == 0)
			ms_exit(section->cmd, &shell->env);
		if (section->field == 1 && pipe((int *)&pfd.cur_r) == -1)
			return (ms_cmd_error("pipe"));
		pid = fork();
		if (pid == -1)
			return (ms_cmd_error("fork"));
		if (pid == 0)
			ms_cmd_exec(section, shell, pfd);
		close(pfd.cur_w);
		close(pfd.prev_r);
		if (section->field == 0)
			close(pfd.cur_r);
		pfd = (t_pipe){.prev_r = pfd.cur_r, .prev_w = pfd.cur_w, -1, -1};
		section++;
		waitpid(pid, 0, WNOHANG);
	}
	return (0);
}

static void	ms_cmd_exec(t_section *section, t_shell *shell, t_pipe pfd)
{
	int		builtins;

	if (pfd.prev_r != -1)
		dup2(pfd.prev_r, STDIN_FILENO);
	if (section->field == 1)
		dup2(pfd.cur_w, STDOUT_FILENO);
	builtins = ms_cmd_is_builtins(section->cmd);
	if (section->cmd->fd_in)
		dup2(section->cmd->fd_in->fd, STDIN_FILENO);
	if (section->cmd->fd_out)
		dup2(section->cmd->fd_out->fd, STDOUT_FILENO);
	if (builtins != -1)
		ms_cmd_exec_builtins((section->cmd), shell, builtins);
	else
		execve("/bin/cat", (*section->cmd).args, shell->env);
	exit(0);
}

static int	ms_cmd_is_builtins(t_command *cmd)
{
	static char	*builtins[] = \
		{"exit", "pwd", "cd", "echo", "export", "env", "unset", 0};
	int			i;

	i = -1;
	while (builtins[++i])
		if (!ft_strncmp(cmd->args[0], builtins[i], ft_strlen(builtins[i]) + 1))
			return (i);
	return (-1);
}

static void	ms_cmd_exec_builtins(t_command *cmd, t_shell *shell, int index)
{
	static t_builtins	builtins[] = \
		{ms_exit, ms_pwd, ms_cd, ms_echo, ms_export, ms_export, ms_unset};

	builtins[index](cmd, &shell->env);
	exit(0);
}

static int	ms_cmd_error(const char *str)
{
	write(STDERR_FILENO, SHELL_NAME, ft_strlen(SHELL_NAME));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
	write(STDERR_FILENO, "\n", 1);
	if (ft_strncmp(str, "pipe", 5))
		return (errno);
	exit(errno);
}
