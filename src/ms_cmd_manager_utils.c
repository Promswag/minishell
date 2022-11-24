/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd_manager_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:34:52 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/24 12:53:41 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_cmd_setup_fd(t_section *section, t_pipe pfd)
{
	if (pfd.prev_r != -1)
		dup2(pfd.prev_r, STDIN_FILENO);
	if (section->field == 1)
		dup2(pfd.cur_w, STDOUT_FILENO);
	if (section->cmd->fd_in)
		dup2(section->cmd->fd_in->fd, STDIN_FILENO);
	if (section->cmd->fd_out)
		dup2(section->cmd->fd_out->fd, STDOUT_FILENO);
}
