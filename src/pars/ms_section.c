/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_section.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:19:42 by aho               #+#    #+#             */
/*   Updated: 2022/11/21 12:27:45 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ms_nbr_section(const char *buff)
{
	int	i;
	int	squote;
	int	dquote;
	int	pipeline;

	i = 0;
	squote = 0;
	dquote = 0;
	pipeline = 1;
	while (buff[i])
	{
		ms_quote_checker(buff, &i, &squote, &dquote);
		if (buff[i] == 124 && squote == 0 && dquote == 0)
			pipeline++;
		i++;
	}
	return (pipeline);
}

void	ms_word(const char *buff, t_section *section)
{
	t_quote	quote;
	int		x;

	x = 0;
	quote.segment = 0;
	quote.i = 0;
	quote.squote = 0;
	quote.dquote = 0;
	quote.chr = 0;
	while (buff[quote.i])
	{
		ms_quote_checker(buff, &quote.i, &quote.squote, &quote.dquote);
		if (buff[quote.i] == 124 && quote.squote == 0 && quote.dquote == 0)
		{
			quote.chr = quote.i - quote.chr;
			section[quote.segment].section = ft_calloc(sizeof(char),
					quote.chr + 1);
			quote.segment++;
			x = 1;
		}
		quote.i++;
	}
	quote.chr = quote.i - quote.chr;
	section[quote.segment].section = ft_calloc(sizeof(char),
			(quote.chr - x + 1));
}

void	ms_word_copy(char *buff, t_section *section)
{
	t_quote	quote;

	quote.segment = 0;
	quote.chr = 0;
	quote.i = 0;
	quote.squote = 0;
	quote.dquote = 0;
	while (buff[quote.i])
	{
		ms_quote_checker(buff, &quote.i, &quote.squote, &quote.dquote);
		if (buff[quote.i] == 124
			&& quote.squote == 0 && quote.dquote == 0)
		{
			section[quote.segment].field = 1;
			quote.segment++;
			quote.chr = 0;
		}
		else
			section[quote.segment].section[quote.chr++] = buff[quote.i];
		quote.i++;
	}
	section[++quote.segment].section = NULL;
}

void	ms_field(t_section *section, int nbr)
{
	int	index;

	index = 0;
	while (index < nbr)
	{
		section[index].field = 0;
		index++;
	}
}

t_section	*ms_section(char *buff, t_fdlst *fdlst)
{
	t_section	*section;
	int			nbr;

	nbr = ms_nbr_section(buff);
	section = calloc(1, sizeof(t_section) * (nbr + 1));
	section->fdlst = fdlst;
	ms_word(buff, section);
	ms_field(section, (nbr) + 1);
	ms_word_copy(buff, section);
	return (section);
}
