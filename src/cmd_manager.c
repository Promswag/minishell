/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:37:42 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/07 17:46:42 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef int	(*t_builtins)(t_command, char ***);
int			ms_command_manager(t_section *section, t_shell *shell);
static int	ms_cmd_exec(t_command cmd, t_shell *shell, int builtins);
static int	ms_cmd_is_builtins(t_command cmd);
static int	ms_cmd_exec_builtins(t_command cmd, t_shell *shell, int index);

int	ms_command_manager(t_section *section, t_shell *shell)
{
	int		i;
	long	fdp[2];

	while (section)
	{
		if ((section + 1) && (section + 1)->field == 1)
		{
			pipe(fdp);
			ms_cmd_exec(*section->cmd, shell);
			section++;
		}
		else
		{
		}
		section++;
	}
	return (0);
}

static int	ms_cmd_exec(t_command cmd, t_shell *shell)
{
	pid_t	pid;
	int		builtins;

	builtins = ms_cmd_is_builtins(cmd);
	if (builtins != -1)
		ms_cmd_exec_builtins(cmd, shell, builtins);
	else
	{
		pid = fork();
		if (!pid)
		{

		}
	}
}

static int	ms_cmd_is_builtins(t_command cmd)
{
	static char	*builtins[] = \
		{"cd",
		"echo",
		"exit",
		"export",
		"pwd",
		"unset",
		0};
	int			i;

	i = -1;
	while (builtins[++i])
		if (!ft_strncmp(cmd.name, builtins[i], ft_strlen(builtins[i])))
			return (i);
	return (-1);
}

static int	ms_cmd_exec_builtins(t_command cmd, t_shell *shell, int index)
{
	static t_builtins	builtins[] = \
		{ms_cd, ms_echo, ms_exit, ms_export, ms_pwd, ms_unset};

	builtins[index](cmd, &shell->env);
}
