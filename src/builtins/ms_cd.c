/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:00:00 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/25 10:53:53 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_cd_error(void)
{
	write(STDERR_FILENO, SHELL_NAME, ft_strlen(SHELL_NAME));
	write(STDERR_FILENO, ": cd: HOME not set\n", 19);
	g_g.exitcode = 1;
}

void	mc_cd_target(char *target, char *oldpwd, char ***env)
{
	char	buf[1000];
	char	*pwd;

	if (target)
	{
		if (chdir(target))
			ms_error_s("cd", target);
		else
		{
			if (getcwd(buf, 1000) == NULL)
				ms_error("cd");
			else
			{
				pwd = ft_strjoin("PWD=", buf);
				ms_export(&(t_command){0, \
					(char *[]){"export", oldpwd, pwd, 0}, 0, 0}, env);
				g_g.exitcode = 0;
				free(pwd);
			}
		}
	}
	else
		ms_cd_error();
}

void	ms_cd(t_command *cmd, char ***env)
{
	char	buf[1000];
	char	*oldpwd;
	char	*target;

	if (getcwd(buf, 1000) == NULL)
	{
		ms_error("cd");
		return ;
	}
	oldpwd = ft_strjoin("OLDPWD=", buf);
	if (cmd->args[1])
		target = cmd->args[1];
	else
		target = ms_export_get_value("HOME", *env);
	mc_cd_target(target, oldpwd, env);
	if (oldpwd)
		free(oldpwd);
	if (!cmd->args[1] && target)
		free(target);
}
