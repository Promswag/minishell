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

t_section	*ms_parsing(char *buff)
{
	t_section	*section;
	t_tmp		*tmp;
	t_fdlst		*fdlst;
	int	index;

	index = 0;
	fdlst = NULL;
	section = ms_section(buff);
	while (section[index].section)
	{
		tmp = NULL;
		tmp = ms_tmp(section[index].section);
		ms_result_fdlst(tmp, &fdlst);
		section[index].cmd = ms_result(tmp);
		index++;
	}
	index = 0;
	while(section[index].section)
	{
		section[index].fdlst = fdlst;
		index++;
	}
//	ms_print_pars(section);
//	while (section[0].fdlst)
//	{
//		printf("%s %d\n", section[0].fdlst->path, section[0].fdlst->type);
//		section[0].fdlst = section[0].fdlst->next;
//	}
	return (section);
}
