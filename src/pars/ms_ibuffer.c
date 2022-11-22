/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ibuffer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aho <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:07:44 by aho               #+#    #+#             */
/*   Updated: 2022/11/14 16:07:45 by aho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// 60, < , 1, 3;

static int	ms_entry_strlen(const char *str, int index)
{
	int	result;

	result = 0;
	while (ft_isdigit(str[index]))
	{
		result++;
		index++;
	}
	return (result);
}

static int	ms_entry_copy(const char *str, int index, char *entry)
{
	int	x;

	x = 0;
	while (ft_isdigit(str[index]))
	{
		entry[x] = str[index];
		index++;
		x++;
	}
	return (index);
}

static char	*ms_add_buffer(int index, t_quote quote, const char *str, char *cpy)
{
	int	end;

	end = 0;
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
			cpy[end++] = str[quote.i++];
		else
			quote.i++;
	}
	return (cpy);
}

static void	ms_count_buffer(int *index, t_quote *quote, const char *str)
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
			quote->segment += ms_expend_length(str, *index);
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

int	ms_ibuffer(t_tmp **tmp, int index, int field_buff, const char *str)
{
	t_quote	quote;
	char	*cpy;
	char	*entry;
	int		result;

	quote.segment = 0;
	quote.squote = 0;
	quote.dquote = 0;
	entry = NULL;
	if (ft_isdigit(str[index]))
	{
		entry = calloc(1, sizeof(char) * (ms_entry_strlen(str, index) + 1));
		index = ms_entry_copy(str, index, entry);
	}
	while (str[index] == 60 || str[index] == ' ')
		index++;
	quote.i = index;
	if ((str[index] == 34 || str[index] == 39) && field_buff == 3)
		field_buff = 12;
	ms_count_buffer(&index, &quote, str);
	cpy = calloc(1, sizeof(char) * (quote.segment + 1));
	result = index;
	ms_add_buffer(result, quote, str, cpy);
	ms_new3(tmp, field_buff, cpy, entry);
	return (result);
}
