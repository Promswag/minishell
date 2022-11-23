/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 13:20:46 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/23 11:58:06 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_echo_option_handler(t_command *cmd, int *i, int *trailing)
{
	int	j;

	while (cmd->args && cmd->args[++*i])
	{
		j = -1;
		if (cmd->args[*i][++j] == '-' && cmd->args[*i][++j] == 'n')
		{
			*trailing = 0;
			while (cmd->args[*i][++j])
			{
				if (cmd->args[*i][j] == 'n' && *i == 0)
					*trailing = 0;
				else if (cmd->args[*i][j] != 'n' && *i == 0)
					*trailing = 1;
				if (cmd->args[*i][j] != 'n')
					return ;
			}
		}
		else
			return ;
	}
}

void	ms_echo(t_command *cmd, char ***env)
{
	int	i;
	int	trailing;

	(void)env;
	i = 0;
	trailing = 1;
	ms_echo_option_handler(cmd, &i, &trailing);
	while (cmd->args && cmd->args[i])
	{
		if (cmd->args[i][0])
			write(STDOUT_FILENO, cmd->args[i], ft_strlen(cmd->args[i]));
		if (cmd->args[i + 1] && *cmd->args[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (trailing)
		write(STDOUT_FILENO, "\n", 1);
	g_exit_code = 0;
}
