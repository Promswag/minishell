/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:30:27 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/18 15:53:13 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_export_delim(char *s)
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

int	ms_export_exists(char *s, char **env)
{
	int	i;
	int	l;

	if (!s)
		return (-1);
	l = 0;
	while (s[l] && s[l] != '=')
		l++;
	i = -1;
	while (env[++i])
	{
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

void	ms_export_destroy(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		free(env[i]);
	free(env);
}
