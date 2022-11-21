/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:00:00 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/21 10:33:07 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_cd(t_command *cmd, char ***env)
{
	char	buf[1000];
	char	*oldpwd;
	char	*pwd;

	getcwd(buf, 1000);
	oldpwd = ft_strjoin("OLDPWD=", buf);
	pwd = ft_strjoin("PWD=", cmd->args[0]);
	if (chdir(cmd->args[0]))
	{
		write(STDERR_FILENO, SHELL_NAME, ft_strlen(SHELL_NAME));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, cmd->name, ft_strlen(cmd->name));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, cmd->args[0], ft_strlen(cmd->args[0]));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
		write(STDERR_FILENO, "\n", 1);
	}
	else
		ms_export(&(t_command){0, (char *[]){oldpwd, pwd, 0}, 0, 0}, env);
	free(oldpwd);
	free(pwd);
	exit(errno);
}
