/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_path_finder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 10:11:25 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/23 13:38:04 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_path_finder(char *name, char **env);
char	*ms_path_finder_generate(char **arr, char *name);
void	ms_path_finder_destroy(char **arr);

char	*ms_path_finder(char *name, char **env)
{
	char	*path_env;
	char	**path_split;
	char	*path;

	if (!access(name, F_OK))
		path = ft_strdup(name);
	else
	{

		path_env = ms_export_get_value("PATH", env);
		if (path_env == NULL)
			return (NULL);
		path_split = ft_split(path_env, ':');
		free(path_env);
		path = ms_path_finder_generate(path_split, name);
		ms_path_finder_destroy(path_split);
	}
	return (path);
}

char	*ms_path_finder_generate(char **arr, char *name)
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

void	ms_path_finder_destroy(char **arr)
{
	int	i;

	i = -1;
	while (arr && arr[++i])
		free(arr[i]);
	if (arr)
		free(arr);
}
