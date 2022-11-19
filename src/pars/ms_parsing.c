/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:28:23 by aho               #+#    #+#             */
/*   Updated: 2022/11/16 17:53:07 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ms_quote_checker(const char *buff,const int *j,
						 int *squote1, int *dquote1)
{
	int	i;
	int	squote;
	int	dquote;

	i = *j;
	squote = *squote1;
	dquote = *dquote1;
	if (buff[i] == 34 && squote == 0) // "
	{
		if (dquote == 0)
			dquote++;
		else if (dquote == 1)
			dquote--;
	}
	if (buff[i] == 39 && dquote == 0) // '
	{
		if (squote == 0)
			squote++;
		else if (squote == 1)
			squote--;
	}
	*squote1 = squote;
	*dquote1 = dquote;
}

int	ms_parsing(char *buff)
{
	t_section	*section;
	t_tmp		*tmp;
	int	index;
	int yank;

	index = 0;
	yank = 0;
	if (!(ms_not_covered(buff)))
		return (ms_errors(1));
	section = ms_section(buff);
	while (section[index].section)
	{
		tmp = ms_tmp(section[index].section);
		section[index].cmd = ms_result(tmp);
		index++;
	}
	index = 0;
	while (section[index].section)
	{
		printf(" -------- ARG ---------- \n");
		while (section[index].cmd.args[yank])
		{
			printf("%s\n", section[index].cmd.args[yank]);
			yank++;
		}
		printf(" -------- FD ----------- \n");
		while (section[index].cmd.unknow)
		{
			printf(" Path = %s, type = %d\n",
				   section[index].cmd.unknow->path, section[index].cmd.unknow->type);
			section[index].cmd.unknow = section[index].cmd.unknow->next;
		}
		yank = 0;
		index++;
	}
	return (0);
}
