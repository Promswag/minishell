/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_fd_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:44:15 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/18 16:57:13 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ms_fd_manager.h"
#include <fcntl.h>

int		ms_fd_manager(t_fdlst *fdlst, t_shell *shell);
void	ms_fd_close(t_fdlst *fdlst, t_shell *shell);
int		ms_fd_error(const char *str);

int	ms_fd_manager(t_fdlst *fdlst, t_shell *shell)
{
	t_fdlst	*tmp;

	shell->stdin_backup = dup(STDIN_FILENO);
	tmp = fdlst;
	while (tmp)
	{
		if (tmp->type == HEREDOC || tmp->type == HEREDOC_QUOTED)
			if (ms_heredoc_handler(tmp, shell->env))
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

void	ms_fd_close(t_fdlst *fdlst, t_shell *shell)
{
	dup2(shell->stdin_backup, STDIN_FILENO);
	(void)shell;
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
