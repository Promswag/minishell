/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_list2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aho <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 12:24:07 by aho               #+#    #+#             */
/*   Updated: 2022/11/19 12:24:08 by aho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static t_fdlst	*ms_lstlast(t_fdlst *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}

static void	ms_lstadd_back(t_fdlst **lst, t_fdlst *new)
{
	if (*lst == NULL)
		*lst = new;
	else
		ms_lstlast(*lst)->next = new;
}


int	ms_new2(t_fdlst **unknow, int field, char *str)
{
	t_fdlst	*elemt;

	elemt = malloc(sizeof(t_tmp));
	if (!(elemt))
		return (0);
	elemt->type = field;
	elemt->path = str;
	elemt->next = NULL;
	ms_lstadd_back(unknow, elemt);
	return (1);
}

