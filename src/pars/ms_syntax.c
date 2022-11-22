/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aho <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:15:51 by aho               #+#    #+#             */
/*   Updated: 2022/11/09 16:56:21 by aho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ms_syntax_error(char const *buff)
{
	if (!(ms_not_covered(buff)))
		return (0);
	return (1);
}

int	ms_not_covered(char const *buff)
{
	t_quote	quote;

	quote.i = -1;
	quote.squote = 0;
	quote.dquote = 0;
	while (buff[++quote.i])
	{
		ms_quote_checker(buff, &quote.i, &quote.squote, &quote.dquote);
	}
	if (quote.squote || quote.dquote)
		return (ms_errors(1));
	return (1);
}