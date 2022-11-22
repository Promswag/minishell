/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_syntax_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aho <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:36:01 by aho               #+#    #+#             */
/*   Updated: 2022/11/22 14:36:02 by aho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

int	ms_newline_errors_in(char const *buff, int index, char chr)
{
	int i;

	index++;
	i = 0;
	while (buff[index])
	{
		if (buff[index] != 0 && buff[index] != chr)
			i = 1;
		index++;
	}
	if (i == 0)
		return (ms_errors(3));
	return (1);
}

int	ms_special_token_in(char const *buff, int index, char chr)
{
	index++;
	if (buff[index])
	{
		if (buff[index] == 62 && chr == 60)
			return (ms_errors(2));
		if (buff[index] == 60 && chr == 60)
			index++;
		if (buff[index] == 60 && chr == 60)
			return (ms_errors(3));
		if (buff[index] == 60 && chr == 62)
			return (ms_errors(3));
		if (buff[index] == 62 && chr == 62)
			index++;
		if (buff[index] == 62 && chr == 62)
			return (ms_errors(3));
	}
	return (1);
}