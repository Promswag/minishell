/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_path_finder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 10:11:25 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/25 14:12:21 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ms_path_finder(char *name, char **env);
static char	*ms_path_finder_generate(char **arr, char *name);
static void	ms_path_finder_destroy(char **arr);
static void	ms_path_invalid(char *str);

char	*ms_path_finder(char *name, char **env)
{
	char	*path_env;
	char	**path_split;
	char	*path;

	path_env = ms_export_get_value("PATH", env);
	path_split = ft_split(path_env, ':');
	if (path_env)
		free(path_env);
	path = ms_path_finder_generate(path_split, name);
	ms_path_finder_destroy(path_split);
	if (!path)
		path = ft_strdup(name);
	if (access(path, F_OK))
		if (ms_cmd_is_builtins(\
			&(t_command){0, (char *[]){name, 0}, 0, 0}) == -1)
			ms_path_invalid(name);
	return (path);
}

static char	*ms_path_finder_generate(char **arr, char *name)
{
	char	*path;
	char	*tmp;

	while (arr && *arr)
	{
		tmp = ft_strjoin(*arr, "/");
		path = ft_strjoin(tmp, name);
		free(tmp);
		if (!access(path, F_OK))
			return (path);
		free(path);
		arr++;
	}
	return (ft_strdup(name));
}

static void	ms_path_finder_destroy(char **arr)
{
	int	i;

	i = -1;
	while (arr && arr[++i])
		free(arr[i]);
	if (arr)
		free(arr);
}

static void	ms_path_invalid(char *str)
{
	write(STDERR_FILENO, SHELL_NAME, ft_strlen(SHELL_NAME));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, ": command not found\n", 20);
}
