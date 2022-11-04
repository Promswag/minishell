/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 13:20:46 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/04 14:27:41 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_echo(t_command cmd, char ***env)
{
	int	i;
	int	j;
	int	trailing;
	int	trigger;

	(void)env;
	i = -1;
	trailing = 1;
	trigger = 0;
	while (cmd.args[++i])
	{
		j = -1;
		if (!trigger && cmd.args[i][++j] == '-' && cmd.args[i][++j] == 'n')
		{
			while (cmd.args[i][++j])
			{
				if (cmd.args[i][j] == 'n' && i == 0)
					trailing = 0;
				else if (cmd.args[i][j] != 'n' && i == 0)
					trailing = 1;
				if (cmd.args[i][j] != 'n')
					trigger = 1;
			}
		}
		if (trigger && cmd.args[i][0])
			write(cmd.out_fd, cmd.args[i], ft_strlen(cmd.args[i]));
		if (trigger && cmd.args[i + 1] && *cmd.args[i + 1])
			write(cmd.out_fd, " ", 1);
	}
	if (trailing)
		write(cmd.out_fd, "\n", 1);
	return (0);
	// exit(0);
}
