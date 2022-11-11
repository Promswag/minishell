/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aho <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 11:18:23 by aho               #+#    #+#             */
/*   Updated: 2022/11/11 11:18:25 by aho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ms_new(t_tmp **tmp, int field, char *str)
{
	t_tmp	*elemt;

	elemt = malloc(sizeof(t_tmp));
	if (!(elemt))
		return (0);
	elemt->field = field;
	elemt->str = str;
	elemt->next = *tmp;
	*tmp = elemt;
	return (1);
}