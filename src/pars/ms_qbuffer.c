/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_qbuffer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aho <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:45:18 by aho               #+#    #+#             */
/*   Updated: 2022/11/14 16:45:19 by aho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// 34 ", 39 ' , 6, 5;

int	ms_qbuffer(t_tmp **tmp, int index, int field_buff, const char *str)
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
		if (str[index] != 39 && str[index] != 34)
			quote.segment++;
		else if (str[index] == 39 && quote.dquote == 1)
			quote.segment++;
		else if (str[index] == 34 && quote.squote == 1)
			quote.segment++;
		index++;
	}
	cpy = malloc(sizeof(char) * (quote.segment + 1));
	cpy[quote.segment + 1] = '\0';
	result = index;
	while (quote.i != index)
	{
		ms_quote_checker(str, &quote.i, &quote.squote, &quote.dquote);
		if (str[quote.i] != 39 && str[quote.i] != 34)
			cpy[end++] = str[quote.i];
		else if (str[quote.i] == 39 && quote.dquote == 1)
			cpy[end++] = str[quote.i];
		else if (str[quote.i] == 34 && quote.squote == 1)
			cpy[end++] = str[quote.i];
		quote.i++;
	}
	ms_new(tmp, field_buff, cpy);
	return (result);
}
