/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:00:00 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/22 17:16:41 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_cd_error(void)
{
	write(STDERR_FILENO, SHELL_NAME, ft_strlen(SHELL_NAME));
	write(STDERR_FILENO, ": cd: HOME not set\n", 19);
	g_exit_code = 1;
	return (1);
}

void	ms_cd_home(char *buf, t_command *cmd, char ***env)
{
	char	*pwd;
	char	*oldpwd;
	char	*home;

	home = ms_export_get_value("HOME", *env);
	if (!home)
	{
		ms_cd_error();
		return ;
	}
	else
		pwd = ft_strjoin("PWD=", home);
	oldpwd = ft_strjoin("OLDPWD=", buf);
	pwd = ft_strjoin("PWD=", home);
	if (chdir(home))
		ms_error_s(cmd->args[0], home);
	else
		ms_export(&(t_command){0, (char *[]){oldpwd, pwd, 0}, 0, 0}, env);
	free(oldpwd);
	free(pwd);
	free(home);
	g_exit_code = 0;
}

void	ms_cd_default(char *buf, t_command *cmd, char ***env)
{
	char	*pwd;
	char	*oldpwd;

	oldpwd = ft_strjoin("OLDPWD=", buf);
	pwd = ft_strjoin("PWD=", cmd->args[1]);
	if (chdir(cmd->args[1]))
		ms_error_s(cmd->args[0], cmd->args[1]);
	else
		ms_export(&(t_command){0, (char *[]){oldpwd, pwd, 0}, 0, 0}, env);
	free(oldpwd);
	free(pwd);
	g_exit_code = 0;
}

void	ms_cd(t_command *cmd, char ***env)
{
	char	buf[1000];

	if (getcwd(buf, 1000) == NULL)
	{
		ms_error("cd");
		return ;
	}
	if (cmd->args[1])
		ms_cd_default(buf, cmd, env);
	else
		ms_cd_home(buf, cmd, env);
}
