/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:28:23 by aho               #+#    #+#             */
/*   Updated: 2022/11/25 13:00:21 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ms_quote_checker(const char *buff, const int *j,
							int *squote1, int *dquote1)
{
	int	i;
	int	squote;
	int	dquote;

	i = *j;
	squote = *squote1;
	dquote = *dquote1;
	if (buff[i] == 34 && squote == 0)
	{
		if (dquote == 0)
			dquote++;
		else if (dquote == 1)
			dquote--;
	}
	if (buff[i] == 39 && dquote == 0)
	{
		if (squote == 0)
			squote++;
		else if (squote == 1)
			squote--;
	}
	*squote1 = squote;
	*dquote1 = dquote;
}

static void	ms_free_tmp(t_tmp *tmp)
{
	t_tmp	*cur;

	while (tmp)
	{
		cur = tmp;
		tmp = tmp->next;
		free(cur);
	}
}

t_section	*ms_parsing(char *buff, char **env)
{
	t_section	*section;
	t_tmp		*tmp;
	t_fdlst		*fdlst;
	int			index;
	int			trigger;

	index = 0;
	trigger = 0;
	fdlst = NULL;
	if (!(ms_syntax_error(buff)))
		return (NULL);
	section = ms_section(buff);
	while (section[index].section)
	{
		tmp = NULL;
		if (trigger)
			g_g.exitcode = 0;
		tmp = ms_tmp(section[index].section, env, &trigger);
		section[index].cmd = ms_result(tmp, &fdlst, env);
		ms_free_tmp(tmp);
		section->fdlst = fdlst;
		index++;
	}
	return (section);
}
