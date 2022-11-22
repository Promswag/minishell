/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:00:00 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/22 11:16:20 by gbaumgar         ###   ########.fr       */
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
	pwd = ft_strjoin("PWD=", cmd->args[1]);
	if (chdir(cmd->args[1]))
		ms_error_s(cmd->args[0], cmd->args[1]);
	else
		ms_export(&(t_command){0, (char *[]){oldpwd, pwd, 0}, 0, 0}, env);
	free(oldpwd);
	free(pwd);
	exit(errno);
}
