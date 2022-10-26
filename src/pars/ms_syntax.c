/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aho <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:34:01 by aho               #+#    #+#             */
/*   Updated: 2022/10/25 16:34:02 by aho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ms_not_covered(char *buff)
{
	t_pars	pars;

	pars.i = -1;
	pars.squote = 0;
	pars.dquote = 0;
	while (buff[++i])
	{
		if (buff[i] == 34 && pars.squote == 0) // "
		{
			if (pars.dquote == 0)
				pars.dquote++;
			else if (pars.dquote == 1)
				pars.dquote--;
		}
		if (buff[i] == 39 && pars.dquote == 0) // '
		{
			if (pars.squote == 0)
				pars.squote++;
			else if (pars.squote == 1)
				pars.squote--;
		}
	}
	if (pars.squote || pars.dquote)
		return (0);
	return (1);
}

int	ms_syntaxe(char *buff)
{
	if (!ms_not_covered(buff))
		return (ms_errors(1));
}
