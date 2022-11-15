/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aho <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 09:27:35 by aho               #+#    #+#             */
/*   Updated: 2022/11/11 09:27:36 by aho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ms_check_buffer(const char *str, int index)
{
	if (str[index] == 60)
	{
		if (str[++index] == 60)
			return (3);
		else
			return (1);
	}
	if (str[index] == 62)
	{
		if (str[++index] == 62)
			return (4);
		else
			return (2);
	}
	if (str[index] == 39)
		return (5);
	if (str[index] == 34)
		return (6);
	return (0);
}

int	ms_buffer_ch(t_tmp **tmp, int index, int field_buff, const char *str)
{
	if (field_buff == 0)
		index = ms_sbuffer(tmp, index, field_buff, str);
	else if (field_buff == 5 || field_buff == 6)
		index = ms_qbuffer(tmp, index, field_buff, str);
	else if (field_buff == 1 || field_buff == 3)
		index = ms_ibuffer(tmp, index, field_buff, str);
	else if (field_buff == 2 || field_buff == 4)
		index = ms_obuffer(tmp, index, field_buff, str);
	return (index);
}

t_tmp	*ms_tmp(char *str)
{
	int		index;
	t_tmp	*tmp;
	int		field_buff;

	index = 0;
	tmp = NULL;
	while (str[index])
	{
		if (str[index] == ' ')
			index++;
		else
		{
			field_buff = ms_check_buffer(str, index);
			index = ms_buffer_ch(&tmp, index, field_buff, str);
		}
	}
	return (tmp);
}