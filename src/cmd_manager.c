/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:37:42 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/11 18:09:44 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef int	(*t_builtins)(t_command, char ***);
int			ms_command_manager(t_section *section, t_shell *shell);
static void	ms_cmd_prepare(t_section section, t_shell *shell, t_pipe pfd);
static void	ms_cmd_exec(t_command cmd, t_shell *shell);
static int	ms_cmd_is_builtins(t_command cmd);
static void	ms_cmd_exec_builtins(t_command cmd, t_shell *shell, int index);
static void	ms_error(const char *str);

int	ms_command_manager(t_section *section, t_shell *shell)
{
	t_pipe		pfd;
	pid_t		pid;

	pfd = (t_pipe){-1, -1, -1, -1};
	while (section->section != NULL)
	{
		if (section->field == 1)
			if (pipe((int *)&pfd.cur_r) == -1)
				ms_error("pipe");
		pid = fork();
		if (pid == -1)
			ms_error("fork");
		if (pid == 0)
		{
			if (section->field == 0 && pfd.prev_r == -1)
				ms_cmd_exec(*section->cmd, shell);
			else
			{
				ms_cmd_prepare(*section, shell, pfd);
			}
		}
		if (pfd.cur_w != -1)
			close(pfd.cur_w);
		if (section->field == 0)
		{
			close(pfd.prev_r);
			close(pfd.cur_r);
		}
		if (section->field == 1 && pfd.prev_r != -1)
		{
			close(pfd.cur_w);
			close(pfd.prev_r);
		}
		if (section->field == 1)
			pfd = (t_pipe){.prev_r = pfd.cur_r, .prev_w = pfd.cur_w, -1, -1};
		section++;
		waitpid(pid, 0, WNOHANG);
	}
	return (0);
}

static void	ms_cmd_prepare(t_section section, t_shell *shell, t_pipe pfd)
{
	if (section.field == 1)
		dup2(pfd.cur_w, STDOUT_FILENO);
	else
		close(pfd.cur_w);
	if (pfd.prev_w != -1)
		dup2(pfd.prev_r, STDIN_FILENO);
	else
		close(pfd.cur_r);
	ms_cmd_exec(*section.cmd, shell);
	exit(0);
}

static void	ms_cmd_exec(t_command cmd, t_shell *shell)
{
	int		builtins;

	// builtins = ms_cmd_is_builtins(cmd);
	// if (builtins == 0)
		// ms_exit(cmd, &shell->env);
	// if (cmd.in_fd != 0)
	// 	dup2(cmd.in_fd, STDIN_FILENO);
	// if (cmd.out_fd != 1)
	// 	dup2(cmd.out_fd, STDOUT_FILENO);
	// if (cmd.err_fd != 2)
	// 	dup2(cmd.err_fd, STDERR_FILENO);
	// printf("%d\n", builtins);
	// if (builtins != -1)
		// ms_cmd_exec_builtins(cmd, shell, builtins);
	// else
	// {
		// printf("eeeee\n");
		execve("/bin/cat", cmd.args, shell->env);
	// }
	exit(0);
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

static void	ms_cmd_exec_builtins(t_command cmd, t_shell *shell, int index)
{
	static t_builtins	builtins[] = \
		{ms_exit, ms_pwd, ms_cd, ms_echo, ms_export, ms_unset};

	builtins[index](cmd, &shell->env);
	exit(0);
}

static void	ms_error(const char *str)
{
	write(STDERR_FILENO, SHELL_NAME, ft_strlen(SHELL_NAME));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
	write(STDERR_FILENO, "\n", 1);
	exit(0);
}
