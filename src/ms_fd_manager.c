/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_fd_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:44:15 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/16 17:38:27 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ms_fd_manager.h"
#include <fcntl.h>

int		ms_fd_manager(t_fdlst *fdlst, char **env);
int		ms_fd_error(const char *str);
void	ms_fd_close(t_fdlst *fdlst);

int	ms_fd_manager(t_fdlst *fdlst, char **env)
{
	t_fdlst	*tmp;

	tmp = fdlst;
	while (tmp)
	{
		if (tmp->type == HEREDOC || tmp->type == HEREDOC_QUOTED)
			if (ms_heredoc_handler(tmp, env))
				return (1);
		tmp = tmp->next;
	}
	tmp = fdlst;
	while (tmp)
	{
		if (tmp->type == REDIR_IN)
			tmp->fd = open(tmp->path, O_RDONLY);
		else if (tmp->type == REDIR_OUT_TRUNCATE)
			tmp->fd = open(tmp->path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (tmp->type == REDIR_OUT_APPEND)
			tmp->fd = open(tmp->path, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (tmp->fd == -1)
			return (ms_fd_error("fd_manager"));
		tmp = tmp->next;
	}
	return (0);
}

void	ms_fd_close(t_fdlst *fdlst)
{
	while (fdlst)
	{
		close(fdlst->fd);
		fdlst = fdlst->next;
	}
}

int	ms_fd_error(const char *str)
{
	write(STDERR_FILENO, SHELL_NAME, ft_strlen(SHELL_NAME));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
	write(STDERR_FILENO, "\n", 1);
	return (1);
}
