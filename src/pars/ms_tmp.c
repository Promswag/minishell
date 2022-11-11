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

int	ms_sbuffer(t_tmp **tmp, int index, int field_buff, const char *str)
{
	int		end;
	char	*cpy;
	int		result;

	end = index;
	while (str[end])
	{
		if (str[end] == ' ')
		{
			end++;
			break ;
		}
		end++;
	}
	cpy = malloc(sizeof(char) * (end - index + 1));
	cpy[end - index] = '\0';
	result = end;
	while (--end != index - 1)
		cpy[end - index] = str[end];
	ms_new(tmp, field_buff, cpy);
	return (result);
}

int	ms_qbuffer(t_tmp **tmp, int index, int field_buff, const char *str)
{
	int		stat;
	int		end;
	char	*cpy;
	int		result;

	stat = field_buff;
	end = index;
	while (str[++end])
	{
		if (str[end] == ' ' && stat == 0)
			break ;
		if (str[end] == 39 && stat == 5)
			stat = 0;
		if (str[end] == 34 && stat == 6)
			stat = 0;
	}
//	printf("%d\n", end);
//	printf("index = %d\n", index);
	cpy = malloc(sizeof(char) * (end - index + 1));
	cpy[end - index] = '\0';
	result = end;
	while (--end != index - 1)
		cpy[end - index] = str[end];
//	printf("%d\n", (int)ft_strlen(cpy));
//	printf(" cpy = %s\n", cpy);
	ms_new(tmp, field_buff, cpy);
	return (result);
}

t_tmp	*ms_tmp(t_section *section)
{
	int		index;
	t_tmp	*tmp;
	int		field_buff;
	int		LaTex;

	LaTex = 0;
	index = 0;
	tmp = NULL;
	while (section[index].section[LaTex])
	{
		if (section[index].section[LaTex] == ' ')
			LaTex++;
		else
		{
			field_buff = ms_check_buffer(section[index].section, LaTex);
			if (field_buff == 0)
				LaTex = ms_sbuffer(&tmp, LaTex,
								   field_buff, section[index].section);
			else if (field_buff == 5 || field_buff == 6)
				LaTex = ms_qbuffer(&tmp, LaTex,
								   field_buff, section[index].section);
		}
	}
	return (tmp);
}