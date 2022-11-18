/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:53:37 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/18 16:51:27 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_debug_print_section(t_section *section)
{
	int	i;

	i = -1;
	if (section)
	{
		printf("\n------------------------------\n");
		printf("SECTION:        %p\n", section);
		printf("SECTION FIELD:  %d\n", section->field);
		printf("SECTION NEXT:   %p\n", section->tmp);
		printf("SECTION CMD:    %p\n", section->cmd);
		if (section->cmd)
		{
			printf("CMD IN:         %d\n", section->cmd->in_fd);
			printf("CMD OUT:        %d\n", section->cmd->out_fd);
			printf("CMD ERR:        %d\n", section->cmd->err_fd);
			printf("CMD NAME:       %s\n", section->cmd->name);
			printf("CMD ARGS:       %p\n", section->cmd->args);
			while (section->cmd->args && section->cmd->args[++i])
				printf("CMD ARGS LIST:  %s\n", section->cmd->args[i]);
		}
		printf("------------------------------\n");
	}
}
