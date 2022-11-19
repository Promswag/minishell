/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_result.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aho <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 11:35:53 by aho               #+#    #+#             */
/*   Updated: 2022/11/19 11:35:55 by aho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

void	ms_result_adress(t_tmp *tmp, t_command cmd)
{
	int	index;

	index = 0;
	while (tmp)
	{
		if (tmp->field == 0 || tmp->field == 5 || tmp->field == 6)
		{
			cmd.args[index] = tmp->str;
			index++;
		}
		tmp = tmp->next;
	}
}

int	ms_result_init_arg(t_tmp *tmp)
{
	int	index;

	index = 0;
	while (tmp)
	{
		if (tmp->field == 0 || tmp->field == 5 || tmp->field == 6)
			index++;
		tmp = tmp->next;
	}
	return (index);
}

void	ms_result_unknow(t_tmp *tmp, t_fdlst **unknow)
{
	while (tmp)
	{
		if (tmp->field == 1 || tmp->field == 2
			|| tmp->field == 3 || tmp->field == 4)
			ms_new2(unknow, tmp->field, tmp->str);
		tmp = tmp->next;
	}
}

t_command	ms_result(t_tmp *tmp)
{
	t_command	result;
	int			index;

	result.unknow = NULL;
	index = ms_result_init_arg(tmp);
	result.args = malloc(sizeof(char *) * index + 1);
	ms_result_adress(tmp, result);
	ms_result_unknow(tmp, &result.unknow);
	return (result);
}