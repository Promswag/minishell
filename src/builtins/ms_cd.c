/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:00:00 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/02 15:25:13 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_cd(t_command cmd, char ***env)
{
	char	buf[1000];
	char	*oldpwd;
	char	*pwd;

	getcwd(buf, 1000);
	oldpwd = ft_strjoin("OLDPWD=", buf);
	pwd = ft_strjoin("PWD=", cmd.args[0]);
	if (chdir(cmd.args[0]))
		printf("%s: %s: %s: %s\n", \
			SHELL_NAME, cmd.name, cmd.args[0], strerror(errno));
	else
		ms_export((t_command){0, (char *[]){oldpwd, pwd, 0}, 0, 0, 0, 0}, env);
	free(oldpwd);
	free(pwd);
	return (errno);
}
