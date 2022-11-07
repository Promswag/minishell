/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aho <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:28:23 by aho               #+#    #+#             */
/*   Updated: 2022/10/25 14:28:24 by aho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ms_quote_checker(const char *buff,const int *j,
						 int *squote1, int *dquote1)
{
	int	i;
	int	squote;
	int	dquote;

	i = *j;
	squote = *squote1;
	dquote = *dquote1;
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
	*squote1 = squote;
	*dquote1 = dquote;
}

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
	int		segment;
	int		chr;

	segment = 0;
	chr = 0;
	quote.i = 0;
	while (buff[quote.i])
	{
		ms_quote_checker(buff, &quote.i, &quote.squote, &quote.dquote);
		if (buff[quote.i] == 124
			&& quote.squote == 0 && quote.dquote == 0)
		{
			segment++;
			chr = 0;
			section[segment].section[chr] = buff[quote.i];
			section[segment].field = 1;
			segment++;
		}
		else
		{
			section[segment].section[chr] = buff[quote.i];
			chr++;
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

	//	count nbr section ; ok
	//	allocation memory ; ok
	//	cpy = count word, allocation, copy

int	ms_parsing(char *buff)
{
	t_section	*section;

	if (!(ms_not_covered(buff)))
		return (ms_errors(1));
	section = ms_section(buff);
	free(section);
	return (0);
}

int	main(void)
{
	char *buff;

	buff = readline(NULL);
	ms_parsing(buff);
	free(buff);
	return 0;
}
