/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:37:42 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/04 16:12:03 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef int	(*t_builtins)(t_command, char ***);

static int	ms_cmd_exec_buitlins(t_command cmd, t_shell *shell, int index)
{
	static t_builtins	builtins[] = \
		{ms_cd, ms_echo, ms_exit, ms_export, ms_pwd, ms_unset};

	builtins[index](cmd, &shell->env);
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
	return (0);
}

int	ms_command_manager(t_command *cmd, t_shell *shell)
{
	int	i;

	i = ms_cmd_is_builtins(*cmd);
	if (!i)
		ms_cmd_exec_builtins(*cmd, shell, i);
	else
	{
		//execve
	}
	return (0);
}
