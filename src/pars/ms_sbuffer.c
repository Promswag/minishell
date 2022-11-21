/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_sbuffer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aho <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:45:11 by aho               #+#    #+#             */
/*   Updated: 2022/11/14 16:45:13 by aho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// 0;

int	ms_sbuffer(t_tmp **tmp, int index, int field_buff, const char *str)
{
	t_quote	quote;
	char	*cpy;
	int		end;
	int		result;

	quote.segment = 0;
	quote.squote = 0;
	quote.dquote = 0;
	end = 0;
	quote.i = index;
	while (str[index])
	{
		if ((str[index] == 60 || str[index] == 62 || str[index] == ' ')
			&& (quote.squote == 0 && quote.dquote == 0))
			break ;
		ms_quote_checker(str, &index, &quote.squote, &quote.dquote);
		if (str[index] == 36 && quote.squote == 0)
		{
			index++;
			quote.segment += ms_expend_length(str, index);
			index = ms_expend_index(str, index);
		}
		else if ((str[index] != 39 && str[index] != 34)
			|| (str[index] == 39 && quote.dquote == 1)
			|| (str[index] == 34 && quote.squote == 1))
		{
			quote.segment++;
			index++;
		}
		else
			index++;
	}
	cpy = malloc(sizeof(char) * (quote.segment + 1));
	cpy[quote.segment] = '\0';
	result = index;
	while (quote.i < index)
	{
		if ((str[quote.i] == 60 || str[quote.i] == 62 || str[quote.i] == ' ')
			&& (quote.squote == 0 && quote.dquote == 0))
			break ;
		ms_quote_checker(str, &quote.i, &quote.squote, &quote.dquote);
		if (str[quote.i] == 36 && quote.squote == 0)
		{
			quote.i++;
			ms_expend_copy(cpy, &quote.i, str, &end);
			quote.i = ms_expend_index(str, quote.i);
		}
		else if ((str[quote.i] != 39 && str[quote.i] != 34)
			|| (str[quote.i] == 39 && quote.dquote == 1)
			|| (str[quote.i] == 34 && quote.squote == 1))
		{
			cpy[end] = str[quote.i];
			end++;
			quote.i++;
		}
		else
			quote.i++;
	}
	ms_new(tmp, field_buff, cpy);
	return (result);
}
