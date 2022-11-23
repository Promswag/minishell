/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:53:37 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/22 12:05:09 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_debug_print_section(t_section *section)
{
	int	i;

	while (section && section->section)
	{
		printf("------------------------------\n");
		printf("SECTION:        %p\n", section);
		printf("SECTION FIELD:  %d\n", section->field);
		printf("SECTION CMD:    %p\n", section->cmd);
		if (section->cmd)
		{
			printf("CMD PATH:       %s\n", section->cmd->path);
			if (section->cmd->fd_in)
				printf("CMD IN:         %d\n", section->cmd->fd_in->fd);
			if (section->cmd->fd_out)
				printf("CMD OUT:        %d\n", section->cmd->fd_out->fd);
			printf("CMD ARGS:       %p\n", section->cmd->args);
			i = -1;
			while (section->cmd->args && section->cmd->args[++i])
				printf("CMD ARGS LIST:  %s\n", section->cmd->args[i]);
		}
		section++;
		if (!section)
			printf("------------------------------\n");
	}
}

void	ms_debug_print_fdlst(t_fdlst *fdlst)
{
	while (fdlst)
	{
		printf("\n%d, %d, %s, %p\n", \
			fdlst->fd, fdlst->type, fdlst->path, fdlst->next);
		fdlst = fdlst->next;
	}
}
