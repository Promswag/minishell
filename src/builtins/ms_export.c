/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:58:06 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/18 15:57:11 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_export_sort(char ***env)
{
	int		i;
	char	*tmp;

	i = 0;
	while ((*env)[++i])
	{
		if (ft_strncmp((*env)[i - 1], (*env)[i], ft_strlen((*env)[i])) > 0)
		{
			tmp = (*env)[i];
			(*env)[i] = (*env)[i - 1];
			(*env)[i - 1] = tmp;
			i = 0;
		}
	}
}

static void	ms_export_add(char *s, char ***env)
{
	int		i;
	char	**new_env;

	i = 0;
	while ((*env)[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	i = -1;
	while ((*env)[++i])
		new_env[i] = ft_strdup((*env)[i]);
	new_env[i++] = ft_strdup(s);
	new_env[i] = 0;
	ms_export_destroy(*env);
	*env = new_env;
}

static int	ms_export_handler(char *s, char ***env)
{
	int	i;

	if (ms_export_delim(s) == -1)
		return (ms_error("export"));
	i = ms_export_exists(s, *env);
	if (i == -1)
		ms_export_add(s, env);
	else
	{
		if (ms_export_delim(s))
		{
			free((*env)[i]);
			(*env)[i] = ft_strdup(s);
		}
	}
	return (0);
}

void	ms_export_print(char **env, int status)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (!status)
		{
			write(STDOUT_FILENO, "declare -x ", 11);
			if (!ms_export_delim(env[i]))
				write(STDOUT_FILENO, env[i], ft_strlen(env[i]));
			else
			{
				write(STDOUT_FILENO, env[i], ms_export_delim(env[i]));
				write(STDOUT_FILENO, "\"", 1);
				write(STDOUT_FILENO, env[i] + ms_export_delim(env[i]), \
					ft_strlen(env[i] + ms_export_delim(env[i])));
				write(STDOUT_FILENO, "\"", 1);
			}
		}
		else if (ms_export_delim(env[i]) > 0)
			write(STDOUT_FILENO, env[i], ft_strlen(env[i]));
		if (!status || ms_export_delim(env[i]) > 0)
			write(STDOUT_FILENO, "\n", 1);
	}
}

void	ms_export(t_command *cmd, char ***env)
{
	int	err;
	int	i;

	err = 0;
	if (!cmd->args)
	{
		ms_export_sort(env);
		if (!ft_strncmp(cmd->name, "export", ft_strlen("export")))
			ms_export_print(*env, 0);
		else
			ms_export_print(*env, 1);
	}
	else
	{
		i = -1;
		while (cmd->args[++i])
			err += ms_export_handler(cmd->args[i], env);
	}
	if (err)
		exit(err);
	exit(EXIT_SUCCESS);
}
