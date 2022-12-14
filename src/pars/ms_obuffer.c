/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_obuffer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aho <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:45:01 by aho               #+#    #+#             */
/*   Updated: 2022/11/14 16:45:03 by aho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// 62, > , 2, 4;

static int	ms_entry_copy(const char *str, int index)
{
	while (ft_isdigit(str[index]))
		index++;
	return (index);
}

static char	*ms_add_buffer(t_quote quote, const char *str,
							char *cpy, char **env)
{
	int			end;
	t_ebuffer	extend;

	end = 0;
	while (str[quote.i] && (quote.i <= quote.chr))
	{
		if ((str[quote.i] == 60 || str[quote.i] == 62 || str[quote.i] == ' ')
			&& (quote.squote == 0 && quote.dquote == 0))
			break ;
		ms_quote_checker(str, &quote.i, &quote.squote, &quote.dquote);
		if (str[quote.i] == 36 && quote.squote == 0)
		{
			extend.x = ++quote.i;
			extend.y = end;
			ms_expend_copy(cpy, &(extend), str, env);
			quote.i = extend.x;
			end = extend.y;
			quote.i = ms_expend_index(str, quote.i);
		}
		else if (ms_line_too_long(str, quote))
			cpy[end++] = str[quote.i++];
		else
			quote.i++;
	}
	return (cpy);
}

static void	ms_count_buffer(int *index, t_quote *quote,
							const char *str, char **env)
{
	while (str[*index])
	{
		if ((str[*index] == 60 || str[*index] == 62 || str[*index] == ' ')
			&& (quote->squote == 0 && quote->dquote == 0))
			break ;
		ms_quote_checker(str, index, &quote->squote, &quote->dquote);
		if (str[*index] == 36 && quote->squote == 0)
		{
			(*index)++;
			quote->segment += ms_expend_length(str, *index, env, quote);
			*index = ms_expend_index(str, *index);
		}
		else if ((str[*index] != 39 && str[*index] != 34)
			|| (str[*index] == 39 && quote->dquote == 1)
			|| (str[*index] == 34 && quote->squote == 1))
		{
			quote->segment++;
			(*index)++;
		}
		else
			(*index)++;
	}
}

int	ms_obuffer(t_tmp **tmp, t_ebuffer ebuffer, const char *str, char **env)
{
	t_quote	quote;
	char	*cpy;

	quote.segment = 0;
	quote.squote = 0;
	quote.dquote = 0;
	quote.trigger = ebuffer.trigger;
	if (ft_isdigit(str[ebuffer.x]))
		ebuffer.x = ms_entry_copy(str, ebuffer.x);
	while (str[ebuffer.x] == 62 || str[ebuffer.x] == ' ')
		ebuffer.x++;
	quote.i = ebuffer.x;
	ms_count_buffer(&(ebuffer.x), &quote, str, env);
	cpy = calloc(1, sizeof(char) * (quote.segment + 1));
	quote.chr = ebuffer.x;
	ms_add_buffer(quote, str, cpy, env);
	ms_new(tmp, ebuffer.y, cpy);
	return (quote.chr);
}
