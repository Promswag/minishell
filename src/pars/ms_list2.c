/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_list2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 12:24:07 by aho               #+#    #+#             */
/*   Updated: 2022/11/21 12:07:00 by gbaumgar         ###   ########.fr       */
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

void	ms_fdlstadd_back(t_fdlst **lst, t_fdlst *new)
{
	if (*lst == NULL)
		*lst = new;
	else
		ms_lstlast(*lst)->next = new;
}

t_fdlst	*ms_new_fdlst(int field, char *str)
{
	t_fdlst	*elem;

	elem = malloc(sizeof(t_fdlst));
	if (!(elem))
		return (NULL);
	elem->fd = -1;
	elem->type = field;
	elem->path = str;
	elem->next = NULL;
	return (elem);
}
