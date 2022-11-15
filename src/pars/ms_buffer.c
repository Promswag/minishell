/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_buffer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aho <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:09:22 by aho               #+#    #+#             */
/*   Updated: 2022/11/14 14:09:23 by aho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ms_cpt_expend(const char *str)
{
	char	*chr;
	int		i;

	i = 0;
	chr = getenv(str);
	while (chr[i])
		i++;
	return (i);
}

//int	ms_sbuffer(t_tmp **tmp, int index, int field_buff, const char *str)
//{
//	int		end;
//	char	*cpy;
//	int		result;
//
//	end = index;
//	while (str[end])
//	{
//		if (str[end] == ' ' || str[end] == 60 || str[end] == 62)
//			break ;
//		end++;
//	}
//	cpy = malloc(sizeof(char) * (end - index + 1));
//	cpy[end - index] = '\0';
//	result = end;
//	while (--end != index - 1)
//		cpy[end - index] = str[end];
//	ms_new(tmp, field_buff, cpy);
//	return (result);
//}

//int	ms_qbuffer(t_tmp **tmp, int index, int field_buff, const char *str)
//{
//	int		stat;
//	int		end;
//	char	*cpy;
//	int		result;
//
//	stat = field_buff;
//	end = index;
//	while (str[++end])
//	{
//		if (str[end] == ' ' && stat == 0)
//			break ;
//		if (str[end] == 39 && stat == 5)
//			stat = 0;
//		if (str[end] == 34 && stat == 6)
//			stat = 0;
//	}
//	cpy = malloc(sizeof(char) * (end - index + 1));
//	cpy[end - index] = '\0';
//	result = end;
//	while (--end != index - 1)
//		cpy[end - index] = str[end];
//	ms_new(tmp, field_buff, cpy);
//	return (result);
//}
