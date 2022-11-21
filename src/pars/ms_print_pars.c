/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_print_pars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aho <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 07:21:58 by aho               #+#    #+#             */
/*   Updated: 2022/11/21 07:21:59 by aho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

void	ms_print_section(t_section *section)
{
	int	index;

	index = 0;
	while (section[index].section)
	{
		printf("%s\n", section[index].section);
		index++;
	}
}

void	ms_print_pars(t_section *section)
{
	int	yank;
	int	index;

	yank = 0;
	index = 0;
	while (section[index].section)
	{
		printf(" -------- ARG ---------- \n");
		while (section[index].cmd.args[yank])
		{
			printf("%s ", section[index].cmd.args[yank]);
			yank++;
		}
		printf("\n -------- FD IN ----------- \n");
		while (section[index].cmd.fd_in)
		{
			printf(" Path = %s, type = %d, entry = %s\n",
				   section[index].cmd.fd_in->path, section[index].cmd.fd_in->type, section[index].cmd.fd_in->entry);
			section[index].cmd.fd_in = section[index].cmd.fd_in->next;
		}
		printf("\n -------- FD OUT ----------- \n");
		while (section[index].cmd.fd_out)
		{
			printf(" Path = %s, type = %d, entry = %s\n",
				   section[index].cmd.fd_out->path, section[index].cmd.fd_out->type, section[index].cmd.fd_out->entry);
			section[index].cmd.fd_out = section[index].cmd.fd_out->next;
		}
		yank = 0;
		index++;
	}
}