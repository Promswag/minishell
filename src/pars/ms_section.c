/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_section.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aho <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:19:42 by aho               #+#    #+#             */
/*   Updated: 2022/11/07 17:19:43 by aho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	while(buff[i])
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
	int	i;
	int	squote;
	int	dquote;
	int segment;
	int	word;

	segment = 0;
	i = 0;
	squote = 0;
	dquote = 0;
	word = 0;
	while(buff[i])
	{
		ms_quote_checker(buff, &i, &squote, &dquote);
		if (buff[i] == 124 && squote == 0 && dquote == 0)
		{
			word = i - word;
			section[segment].section = ft_calloc(sizeof(char), word);
			segment++;
			section[segment].section = ft_calloc(sizeof(char), 1);
			segment++;
		}
		i++;
	}
	section[segment].section = ft_calloc(sizeof(char), word);
}

void	ms_word_copy(char *buff, t_section *section)
{
	t_quote	quote;

	quote.segment = 0;
	quote.chr = 0;
	quote.i = 0;
	while (buff[quote.i])
	{
		ms_quote_checker(buff, &quote.i, &quote.squote, &quote.dquote);
		if (buff[quote.i] == 124
			&& quote.squote == 0 && quote.dquote == 0)
		{
			quote.segment++;
			quote.chr = 0;
			section[quote.segment].section[quote.chr] = buff[quote.i];
			section[quote.segment].field = 1;
			quote.segment++;
		}
		else
		{
			section[quote.segment].section[quote.chr] = buff[quote.i];
			quote.chr++;
		}
		quote.i++;
	}
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

t_section	*ms_section(char *buff)
{
	t_section	*section;
	int 		nbr;
	int			index;

	index = 0;
	nbr = ms_nbr_section(buff);
	section = malloc(sizeof(t_section) * (nbr + (nbr - 1)));
	ms_word(buff, section);
	ms_field(section, (nbr + (nbr - 1)));
	ms_word_copy(buff, section);
	while(index < (nbr + (nbr - 1)))
	{
		printf(" ------------------ \n");
		printf("section = %s\nfield = %d\nnbr tab = %d\n",
			   section[index].section, section[index].field, index);
		index++;
	}
	return (section);
}