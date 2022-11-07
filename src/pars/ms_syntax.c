/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aho <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:15:51 by aho               #+#    #+#             */
/*   Updated: 2022/11/07 11:15:52 by aho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ms_not_covered(char *buff)
{
	t_quote	quote;

	quote.i = -1;
	quote.squote = 0;
	quote.dquote = 0;
	while (buff[++quote.i])
	{
		if (buff[quote.i] == 34 && quote.squote == 0) // "
		{
			if (quote.dquote == 0)
				quote.dquote++;
			else if (quote.dquote == 1)
				quote.dquote--;
		}
		if (buff[quote.i] == 39 && quote.dquote == 0) // '
		{
			if (quote.squote == 0)
				quote.squote++;
			else if (quote.squote == 1)
				quote.squote--;
		}
	}
	if (quote.squote || quote.dquote)
		return (0);
	return (1);
}
