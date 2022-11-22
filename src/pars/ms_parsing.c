/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:28:23 by aho               #+#    #+#             */
/*   Updated: 2022/11/21 14:32:57 by gbaumgar         ###   ########.fr       */
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
	int			index;

	index = 0;
	fdlst = NULL;
	if (!(ms_syntax_error(buff)))
		return (NULL);
	section = ms_section(buff, fdlst);
	while (section[index].section)
	{
		tmp = NULL;
		tmp = ms_tmp(section[index].section);
		section[index].cmd = ms_result(tmp, &fdlst);
		section->fdlst = fdlst;
		index++;
	}
	return (section);
}
