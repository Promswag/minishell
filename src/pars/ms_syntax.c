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

int	ms_syntax_chr(char const *buff, int result)
{
	int	i;
	int	statut;

	statut = 0;
	i = 0;
	while (buff[i] && result)
	{
		if (buff[i] != 124 && buff[i] != ' ')
			statut = 1;
		else if (statut == 0 && buff[i] != ' ')
			return (ms_errors(3));
		else if (buff[i] == 124)
			statut = 0;
		if (buff[i] == 60 || buff[i] == 62)
		{
			result = ms_special_token_in(buff, i, buff[i]);
			if (result == 1)
				result = ms_newline_errors_in(buff, i, buff[i]);
		}
		i++;
	}
	if (statut == 0)
		return (ms_errors(3));
	return (result);
}

static int	ms_void(char const *buff)
{
	int	i;
	int	x;

	x = 1;
	i = 0;
	while (buff[i])
	{
		if (buff[i] != ' ')
			x = 0;
		i++;
	}
	return (x);
}

int	ms_syntax_error(char const *buff)
{
	int	result;

	result = 1;
	if (ms_void(buff))
		return (result);
	if (!(ms_not_covered(buff)))
		return (0);
	result = ms_syntax_chr(buff, result);
	return (result);
}
