/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_fd_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:44:15 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/15 16:13:41 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ms_fd_manager.h"

void	ms_fd_manager(t_fdlst *fdlst, char **env);
void	ms_fd_error(const char *str);

void	ms_fd_manager(t_fdlst *fdlst, char **env)
{
	t_fdlst	*tmp;

	tmp = fdlst;
	while (tmp)
	{
		if (tmp->type == HEREDOC || tmp->type == HEREDOC_QUOTED)
			ms_heredoc_handler(tmp, env);
		tmp = tmp->next;
	}
}

void	ms_fd_error(const char *str)
{
	write(STDERR_FILENO, SHELL_NAME, ft_strlen(SHELL_NAME));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
	write(STDERR_FILENO, "\n", 1);
}
