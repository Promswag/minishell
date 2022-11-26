/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_path_finder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 10:11:25 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/26 14:58:37 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

char		*ms_path_finder(char *name, char **env);
static char	*ms_path_finder_generate(char **arr, char *name);
static void	ms_path_finder_destroy(char **arr);
static int	ms_path_invalid(char *name);
static char	*ms_path_absolute(char *str);

char	*ms_path_finder(char *name, char **env)
{
	char		*path_env;
	char		**path_split;
	char		*path;

	if (!ft_strchr(name, '/'))
	{
		if (ms_cmd_is_builtins(\
			&(t_command){0, (char *[]){name, 0}, 0, 0}) != -1)
			return (ft_strdup(name));
		path_env = ms_export_get_value("PATH", env);
		path_split = ft_split(path_env, ':');
		if (path_env)
			free(path_env);
		path = ms_path_finder_generate(path_split, name);
		ms_path_finder_destroy(path_split);
		if (path)
			return (path);
		path = ft_strdup("/");
	}
	else
		path = ms_path_absolute(name);
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
	return (NULL);
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

static int	ms_path_invalid(char *name)
{
	struct stat	sf;
	int			err;

	if (ft_strchr(name, '/'))
	{
		err = stat(name, &sf);
		if (!err && sf.st_mode & S_IFDIR)
			return (ms_path_error(name, "is a directory"));
		else if (!err && sf.st_mode & S_IFREG)
		{
			if (access(name, X_OK))
				return (ms_path_error(name, "Permission denied"));
			else
				return (0);
		}
		else if (access(name, X_OK) && errno == EACCES)
			return (ms_path_error(name, "Permission denied"));
		else
			return (ms_path_error(name, "No such file or directory"));
	}
	return (ms_path_error(name, "command not found"));
}

static char	*ms_path_absolute(char *str)
{
	char	buf[1000];
	char	*tmp;
	char	*res;

	if (str && *str == '/')
		return (ft_strdup(str));
	getcwd(buf, 1000);
	tmp = ft_strjoin(buf, "/");
	res = ft_strjoin(tmp, str);
	free(tmp);
	return (res);
}
