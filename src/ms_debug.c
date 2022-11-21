/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:53:37 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/21 13:02:08 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_debug_print_section(t_section *section)
{
	int	i;

	i = -1;
	while (section && section->section)
	{
		printf("\n------------------------------\n");
		printf("SECTION:        %p\n", section);
		printf("SECTION FIELD:  %d\n", section->field);
		printf("SECTION CMD:    %p\n", section->cmd);
		if (section->cmd)
		{
			if (section->cmd->fd_in)
				printf("CMD IN:         %d\n", section->cmd->fd_in->fd);
			if (section->cmd->fd_out)
				printf("CMD OUT:        %d\n", section->cmd->fd_out->fd);
			// printf("CMD NAME:       %s\n", section->cmd->name);
			printf("CMD ARGS:       %p\n", section->cmd->args);
			while (section->cmd->args && section->cmd->args[++i])
				printf("CMD ARGS LIST:  %s\n", section->cmd->args[i]);
		}
		printf("------------------------------\n");
		section++;
	}
}

void	ms_debug_print_fdlst(t_fdlst *fdlst)
{
	while (fdlst)
	{
		printf("%d, %d, %s, %p\n", fdlst->fd, fdlst->type, fdlst->path, fdlst->next);
		fdlst = fdlst->next;
	}
}
