/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_fd_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:44:15 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/22 13:58:23 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ms_fd_manager.h"
#include <fcntl.h>

int		ms_fd_manager(t_fdlst *fdlst, t_shell *shell);
void	ms_fd_close(t_fdlst *fdlst, t_shell *shell);

int	ms_fd_manager(t_fdlst *fdlst, t_shell *shell)
{
	t_fdlst	*tmp;

	tmp = fdlst;
	while (tmp && g_exit_code != -1)
	{
		if (tmp->type == HEREDOC || tmp->type == HEREDOC_QUOTED)
			if (ms_heredoc_handler(tmp, shell->env))
				return (ms_error("heredoc"));
		tmp = tmp->next;
	}
	tmp = fdlst;
	while (tmp && g_exit_code != -1)
	{
		if (tmp->type == REDIR_IN)
			tmp->fd = open(tmp->path, O_RDONLY);
		else if (tmp->type == REDIR_OUT_TRUNCATE)
			tmp->fd = open(tmp->path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (tmp->type == REDIR_OUT_APPEND)
			tmp->fd = open(tmp->path, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (tmp->fd == -1)
			return (ms_error(tmp->path));
		tmp = tmp->next;
	}
	return (0);
}

void	ms_fd_close(t_fdlst *fdlst, t_shell *shell)
{
	dup2(shell->stdin_backup, STDIN_FILENO);
	dup2(shell->stdout_backup, STDOUT_FILENO);
	while (fdlst)
	{
		close(fdlst->fd);
		fdlst = fdlst->next;
	}
}
