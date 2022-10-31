/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:58:06 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/10/31 18:18:59 by gbaumgar         ###   ########.fr       */
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
	int	x;
	int	d;

	d = ms_export_delim(s);
	i = -1;
	while (env[++i])
	{
		x = ms_export_delim(env[i]);
		if (!ft_strncmp(s, env[i], ft_strlen(s)))
		{
			if (env[i][ft_strlen(s)] == '=')
				return (i);
		}
	}
	return (-1);
}

static int	ms_export_length(t_command cmd, char **env)
{
	int		i;
	int		c;

	i = -1;
	c = 0;
	while (env[++i])
		c++;
	i = -1;
	while (cmd.args[++i])
	{
		if ((ft_isalpha(*cmd.args[i]) || *cmd.args[i] == '_') && \
			ms_export_exists(cmd.args[i], env) == -1)
			c++;
	}
	printf("%d\n", c);
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

static int	ms_export_add(t_command cmd, char ***env)
{
	int		error;
	char	**tmp;
	int		i;
	int		j;
	int		cursor;

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
			write(cmd.err_fd, "export: `", 9);
			write(cmd.err_fd, cmd.args[j], ft_strlen(cmd.args[j]));
			write(cmd.err_fd, "': not a valid identifier\n", 26);
			printf("%lu\n", sizeof("': not a valid identifier\n"));
			printf("%lu\n", sizeof("export: `"));
		}
		else
		{
			cursor = ms_export_exists(cmd.args[j], *env);
			printf("%d\n", cursor);
			if (cursor == -1)
				tmp[i++] = ft_strdup(cmd.args[j]);
			else
			{	
				free(tmp[cursor]);
				tmp[cursor] = ft_strdup(cmd.args[j]);
			}
		}
	}
	tmp[i] = 0;
	ms_export_destroy(*env);
	*env = tmp;
	if (error)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ms_export_display(t_command cmd, char ***env)
{
	int	i;

	i = -1;
	ms_export_sort(env);
	while ((*env)[++i])
	{
		write(cmd.out_fd, "declare -x ", 11);
		if (!ms_export_delim((*env)[i]))
		{
			write(cmd.out_fd, (*env)[i], ft_strlen((*env)[i]));
			write(cmd.out_fd, "\n", 1);
		}
		else
		{
			write(cmd.out_fd, (*env)[i], ms_export_delim((*env)[i]));
			write(cmd.out_fd, "\"", 1);
			write(cmd.out_fd, (*env)[i] + ms_export_delim((*env)[i]), \
				ft_strlen((*env)[i] + ms_export_delim((*env)[i])));
			write(cmd.out_fd, "\"\n", 2);
		}
	}
	return (EXIT_SUCCESS);
}

int	ms_export(t_command cmd, char ***env)
{
	if (!cmd.args)
		return (ms_export_display(cmd, env));
	else
		return (ms_export_add(cmd, env));
}
