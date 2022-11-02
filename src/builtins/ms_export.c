/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:58:06 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/02 15:17:04 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_export_delim(char *s)
{
	int	i;

	i = -1;
	if (!ft_isalpha(*s) && *s != '_')
		return (-1);
	while (s[++i])
	{
		if (s[i] == '=')
			return (++i);
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (-1);
	}
	return (0);
}

static int	ms_export_exists(char *s, char **env)
{
	int	i;
	int	l;

	l = 0;
	while (s[l] && s[l] != '=')
		l++;
	i = -1;
	while (env[++i])
	{
		// printf("%d\n", i);
		// printf("%d\n", l);
		// printf("%s\n", s);
		// printf("%s\n", env[i]);
		if (!ft_strncmp(s, env[i], l))
			if (env[i][l] == '=' || env[i][l] == '\0')
				return (i);
	}
	return (-1);
}

char	*ms_export_get_value(char *s, char **env)
{
	int	i;

	i = ms_export_exists(s, env);
	if (i != -1)
		return (ft_strdup(env[i] + ms_export_delim(env[i])));
	else
		return (NULL);
}

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

void	ms_export_destroy(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		free(env[i]);
	free(env);
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

int	ms_export_handler(t_command cmd, char *s, char ***env)
{
	int	i;

	if (ms_export_delim(s) == -1)
	{
		write(cmd.err_fd, "export: `", 9);
		write(cmd.err_fd, s, ft_strlen(s));
		write(cmd.err_fd, "': not a valid identifier\n", 26);
		return (1);
	}
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

void	ms_export_print(int fd, char **env, int status)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (!status)
		{
			write(fd, "declare -x ", 11);
			if (!ms_export_delim(env[i]))
				write(fd, env[i], ft_strlen(env[i]));
			else
			{
				write(fd, env[i], ms_export_delim(env[i]));
				write(fd, "\"", 1);
				write(fd, env[i] + ms_export_delim(env[i]), \
					ft_strlen(env[i] + ms_export_delim(env[i])));
				write(fd, "\"", 1);
			}
			write(fd, "\n", 1);
		}
		else if (ms_export_delim(env[i]) > 0)
		{
			write(fd, env[i], ft_strlen(env[i]));
			write(fd, "\n", 1);
		}
	}
}

int	ms_export(t_command cmd, char ***env)
{
	int	err;
	int	i;

	err = 0;
	if (!cmd.args)
	{
		ms_export_sort(env);
		ms_export_print(cmd.out_fd, *env, 0);
	}
	else
	{
		i = -1;
		while (cmd.args[++i])
			err += ms_export_handler(cmd, cmd.args[i], env);
	}
	return (err);
}
