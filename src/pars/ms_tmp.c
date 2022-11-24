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

#include "parser.h"

int	ms_entry(const char *str, int index)
{
	while (ft_isdigit(str[index]))
		index++;
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
	return (0);
}

int	ms_check_buffer(const char *str, int index)
{
	if (ft_isdigit(str[index]))
		return (ms_entry(str, index));
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

int	ms_buffer_ch(t_tmp **tmp, t_ebuffer ebuffer, const char *str, char **env)
{
	if (ebuffer.y == 0)
		ebuffer.x = ms_sbuffer(tmp, ebuffer, str, env);
	else if (ebuffer.y == 5 || ebuffer.y == 6)
		ebuffer.x = ms_qbuffer(tmp, ebuffer, str, env);
	else if (ebuffer.y == 1 || ebuffer.y == 3)
		ebuffer.x = ms_ibuffer(tmp, ebuffer, str, env);
	else if (ebuffer.y == 2 || ebuffer.y == 4)
		ebuffer.x = ms_obuffer(tmp, ebuffer, str, env);
	return (ebuffer.x);
}

t_tmp	*ms_tmp(char *str, char **env, int *trigger)
{
	int			index;
	t_tmp		*tmp;
	int			field_buff;
	t_ebuffer	ebuffer;

	ebuffer.trigger = trigger;
	index = 0;
	tmp = NULL;
	while (str[index])
	{
		if (str[index] == ' ')
			index++;
		else
		{
			field_buff = ms_check_buffer(str, index);
			ebuffer.x = index;
			ebuffer.y = field_buff;
			index = ms_buffer_ch(&tmp, ebuffer, str, env);
		}
	}
	return (tmp);
}
