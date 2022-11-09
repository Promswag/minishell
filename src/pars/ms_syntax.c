/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aho <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:15:51 by aho               #+#    #+#             */
/*   Updated: 2022/11/09 16:32:41 by aho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ms_not_covered(char *buff)
{
	int	i;
	int	squote;
	int	dquote;

	i = -1;
	squote = 0;
	dquote = 0;
	while (buff[++i])
	{
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
	}
	if (squote || dquote)
		return (0);
	return (1);
}

int	ms_syntaxe(char *buff)
{
	if (!ms_not_covered(buff))
		return (ms_errors(1));
	return (1);
}
