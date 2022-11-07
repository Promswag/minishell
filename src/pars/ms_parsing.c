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
