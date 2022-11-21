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
	if (str[index] == '?')
		i += (int)ft_strlen(ft_itoa(g_exit_code));
	else if (!(ft_isalpha(str[index]) || (str[index] == '_')))
		return (i);
	else
	{
		while (ft_isalpha(str[i]) || str[i] == '_')
			i++;
	}
	return (i);
}

char	*ms_expend_getname(const char *str, int index)
{
	int		i;
	char	*name;
	int		length;

	i = index;
	if (str[index] == '?')
		return (ft_itoa(g_exit_code));
	else if (!(ft_isalpha(str[index]) || (str[index] == '_')))
		return ("$");
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
	if (str[index] == '?')
		chr = ft_itoa(g_exit_code);
	else if (!(ft_isalpha(str[index]) || (str[index] == '_')))
		return (1);
	else
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
	if (str[*i] == '?')
		chr = ft_itoa(g_exit_code);
	else if (!(ft_isalpha(str[*i]) || (str[*i] == '_')))
	{
		cpy[*end] = '$';
		(*end)++;
		return ;
	}
	else
		chr = getenv(name);
	if (!chr)
		return ;
	while (chr[index])
	{
		cpy[*end] = chr[index];
		(*end)++;
		index++;
	}
}