/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:58:06 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/10/31 13:49:45 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_export_length(t_command cmd, char **env)
{
	int		i;
	int		c;

	i = -1;
	c = 0;
	while (cmd.args[++i])
		if (*cmd.args[i] != '-')
			c++;
	i = -1;
	while (env[++i])
		c++;
	return (c);
}

void	ms_export_sort(char ***env)
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
	return (-1);
}

static int	ms_export_add(t_command cmd, char ***env)
{
	int		error;
	char	**tmp;
	int		i;
	int		j;

	error = 0;
	tmp = malloc(sizeof(char *) * (ms_export_length(cmd, *env) + 1));
	i = -1;
	while ((*env)[++i])
		tmp[i] = ft_strdup((*env)[i]);
	j = -1;
	while (cmd.args[++j])
	{
		if (ms_export_delim(cmd.args[j]) == -1 && ++error)
		{
			write(2, "export: `", 9);
			write(2, cmd.args[j], ft_strlen(cmd.args[j]));
			write(2, "': not a valid identifier\n", 26);
		}
		else
			tmp[i++] = ft_strdup(cmd.args[j]);
	}
	tmp[i] = 0;
	ms_export_destroy(*env);
	*env = tmp;
	return (error);
}

int	ms_export(t_command cmd, char ***env)
{
	int	i;

	if (!cmd.args)
	{
		ms_export_sort(env);
		i = -1;
		while ((*env)[++i])
		{
			write(cmd.fd, "declare -x ", 11);
			write(cmd.fd, (*env)[i], ms_export_delim((*env)[i]));
			write(cmd.fd, "\"", 1);
			write(cmd.fd, (*env)[i] + ms_export_delim((*env)[i]), \
				ft_strlen((*env)[i] + ms_export_delim((*env)[i])));
			write(cmd.fd, "\"\n", 2);
		}
		return (EXIT_SUCCESS);
	}
	else
	{
		if (ms_export_add(cmd, env))
			return (EXIT_FAILURE);
		else
			return (EXIT_SUCCESS);
	}
}
