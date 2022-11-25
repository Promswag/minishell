/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:27:29 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/25 10:53:53 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_pwd(t_command *cmd, char ***env)
{
	char	path[100];

	(void)cmd;
	(void)env;
	if (getcwd(path, 1000) == NULL)
	{
		ms_error("cd");
		return ;
	}
	write(STDOUT_FILENO, path, ft_strlen(path));
	write(STDOUT_FILENO, "\n", 1);
	g_g.exitcode = 0;
}
