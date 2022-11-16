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

#include "parser.h"

static t_tmp	*ms_lstlast(t_tmp *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}

static void	ms_lstadd_back(t_tmp **lst, t_tmp *new)
{
	if (*lst == NULL)
		*lst = new;
	else
		ms_lstlast(*lst)->next = new;
}

int	ms_new(t_tmp **tmp, int field, char *str)
{
	t_tmp	*elemt;

	elemt = malloc(sizeof(t_tmp));
	if (!(elemt))
		return (0);
	elemt->field = field;
	elemt->str = str;
	elemt->next = NULL;
	ms_lstadd_back(tmp, elemt);
	return (1);
}