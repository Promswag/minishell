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
		i++;
	else if (!(ft_isalnum(str[index])) && str[index] != '_')
		return (i);
	else
	{
		while (ft_isalnum(str[i]) || str[i] == '_')
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
	else if (!(ft_isalnum(str[index])) && str[index] != '_')
		return ("$");
	length = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
	{
		i++;
		length++;
	}
	name = calloc(1, (length + 1) * sizeof(char));
	i = index;
	length = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
	{
		name[length] = str[i];
		length++;
		i++;
	}
	return (name);
}

int	ms_expend_length(const char *str, int index, char **env)
{
	char	*name;
	char	*chr;
	int		i;

	i = 0;
	name = ms_expend_getname(str, index);
	if (str[index] == '?')
		chr = ft_itoa(g_exit_code);
	else if (!(ft_isalnum(str[index])) && str[index] != '_')
		return (1);
	else
		chr = ms_export_get_value(name, env);
	if (!chr)
		return (0);
	while (chr[i])
		i++;
	return (i);
}

void	ms_expend_copy(char *cpy, t_ebuffer *expend,
						const char *str, char **env)
{
	char	*name;
	char	*chr;
	int		index;

	index = 0;
	name = ms_expend_getname(str, expend->x);
	if (str[expend->x] == '?')
	{
		chr = ft_itoa(g_exit_code);
		g_exit_code = 0;
	}
	else if (!(ft_isalnum(str[expend->x])) && str[expend->x] != '_')
	{
		cpy[(expend->y)++] = '$';
		return ;
	}
	else
		chr = ms_export_get_value(name, env);
	if (!chr || !(chr[0]))
		return ;
	while (chr[index])
	{
		cpy[expend->y] = chr[index++];
		(expend->y)++;
	}
}

int	ms_line_too_long(const char *str, t_quote quote)
{
	if ((str[quote.i] != 39 && str[quote.i] != 34)
		|| (str[quote.i] == 39 && quote.dquote == 1)
		|| (str[quote.i] == 34 && quote.squote == 1))
		return (1);
	return (0);
}
