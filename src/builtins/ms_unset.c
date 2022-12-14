/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:00:41 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/25 10:53:53 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_unset_is_name(char *s)
{
	int	i;

	i = -1;
	if (!ft_isalpha(*s) && *s != '_')
		return (0);
	while (s[++i])
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
	return (1);
}

static void	ms_unset_remove(char *s, char ***env)
{
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	while ((*env)[i])
		i++;
	new_env = malloc(sizeof(char *) * i);
	i = -1;
	j = 0;
	while ((*env)[++i])
	{
		if (!ft_strncmp(s, (*env)[i], ft_strlen(s)) \
			&& ((*env)[i][ft_strlen(s)] == 0 || (*env)[i][ft_strlen(s)] == '='))
			continue ;
		else
			new_env[j++] = ft_strdup((*env)[i]);
	}
	new_env[j] = 0;
	ms_export_destroy(*env);
	*env = new_env;
}

void	ms_unset(t_command *cmd, char ***env)
{
	int		err;
	int		i;
	char	*id;
	char	*tmp;

	err = 0;
	i = 0;
	while (cmd->args[++i])
	{
		if (ms_unset_is_name(cmd->args[i]))
		{
			if (ms_export_exists(cmd->args[i], *env) != -1)
				ms_unset_remove(cmd->args[i], env);
		}
		else
		{
			tmp = ft_strjoin("`", cmd->args[i]);
			id = ft_strjoin(tmp, "'");
			ms_error_s("unset", id);
			free(tmp);
			free(id);
			err++;
		}
	}
	g_g.exitcode = err;
}
