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

#include "parser.h"

int	ms_expend_index(const char *str, int index)
{
	int		i;

	i = index;
	while (ft_isalpha(str[i]) || str[i] == '_')
		i++;
	return (i);
}

char	*ms_expend_getname(const char *str, int index)
{
	int		i;
	char	*name;
	int		length;

	i = index;
	while(str[i] == ' ')
		i++;
	length = 0;
	while (ft_isalpha(str[i]) || str[i] == '_')
	{
		i++;
		length++;
	}
	name = malloc((length + 1) * sizeof(char));
	name[length] = '\0';
	i = index;
	length = 0;
	while (ft_isalpha(str[i]) || str[i] == '_')
	{
		name[length] = str[i];
		length++;
		i++;
	}
	return (name);
}

int	ms_expend_length(const char *str, int index)
{
	char	*name;
	char	*chr;
	int		i;

	i = 0;
	name = ms_expend_getname(str, index);
	chr = getenv(name);
	if (!chr)
		return (0);
	while (chr[i])
		i++;
	return (i);
}

void	ms_expend_copy(char *cpy,int *i, const char *str, int *end)
{
	char	*name;
	char	*chr;
	int		index;

	index = 0;
	name = ms_expend_getname(str, *i);
	chr = getenv(name);
	if (!chr)
	{
		cpy[*end] = 0;
		(*end)++;
		return ;
	}
	while (chr[index])
	{
		cpy[*end] = chr[index];
		(*end)++;
		index++;
	}
}