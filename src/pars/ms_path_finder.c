/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_path_finder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 10:11:25 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/25 20:52:48 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

char		*ms_path_finder(char *name, char **env);
static char	*ms_path_finder_generate(char **arr, char *name);
static void	ms_path_finder_destroy(char **arr);
static void	ms_path_invalid(char *name, char *path);

char	*ms_path_absolute(char *str)
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
		if (!path)
		{
			ms_path_invalid(name, path);
			path = ft_strdup(name);
		}
	}
	else
	{
		path = ms_path_absolute(name);
		ms_path_invalid(name, path);
	}
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

static void	ms_path_invalid(char *name, char *path)
{
	struct stat	sf;
	int			err;

	err = stat(path, &sf);
	printf("\n|err = %d, errno = %d|\n", err, errno);
	printf("%d\n", sf.st_mode);
	printf("name = %s, path = %s\n", name, path);
	if (ft_strchr(name, '/'))
	{
		write(STDERR_FILENO, SHELL_NAME, ft_strlen(SHELL_NAME));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, name, ft_strlen(name));
		if (err == -1 && errno == ENOENT)
			write(STDERR_FILENO, ": No such file or directory\n", \
				ft_strlen(": No such file or directory\n"));
		else if (sf.st_mode & S_IXUSR)
			write(STDERR_FILENO, ": Permission denied\n", \
				ft_strlen(": Permission denied\n"));
		else if (sf.st_mode & S_IFDIR)
			write(STDERR_FILENO, ": is a directory\n", \
				ft_strlen(": is a directory\n"));
		return ;
	}
	if (access(path, F_OK))
	{
		write(STDERR_FILENO, SHELL_NAME, ft_strlen(SHELL_NAME));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, name, ft_strlen(name));
		write(STDERR_FILENO, ": command not found\n", \
			ft_strlen(": command not found\n"));
		return ;
	}
}
