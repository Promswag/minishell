/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:58:06 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/10/28 17:05:16 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ms_export_sort(char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (env[++i])
	{
		if (ft_strncmp(env[i - 1], env[i], ft_strlen(env[i])) > 0)
		{
			tmp = env[i]; 
			env[i] = env[i - 1];
			env[i - 1] = tmp;
			i = 0;
		}
	}
	return (env);
}

int	ms_export(t_command cmd, char **env)
{
	if (!cmd.args)
	{
		env = ms_export_sort(env);
		while (env && *env)
		{
			write(cmd.fd, "declare -x ", 11);
			write(cmd.fd, *env, ft_strlen(*env++));
			write(cmd.fd, "\n", 1);
		}
	}
	else
	{

	}
}
