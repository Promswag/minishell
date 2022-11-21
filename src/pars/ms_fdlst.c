/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_fdlst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aho <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:26:45 by aho               #+#    #+#             */
/*   Updated: 2022/11/21 13:26:46 by aho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

void	ms_result_fdlst(t_tmp *tmp, t_fdlst **unknow)
{
	while (tmp)
	{
		if (tmp->field == 1)
			ms_new2(unknow, REDIR_IN, tmp->str, tmp->entry);
		if (tmp->field == 3)
			ms_new2(unknow, HEREDOC, tmp->str, tmp->entry);
		if (tmp->field == 2)
			ms_new2(unknow, REDIR_OUT_TRUNCATE, tmp->str, tmp->entry);
		if (tmp->field == 4)
			ms_new2(unknow, REDIR_OUT_APPEND, tmp->str, tmp->entry);
		if (tmp->field == 12)
			ms_new2(unknow, HEREDOC_QUOTED, tmp->str, tmp->entry);
		tmp = tmp->next;
	}
}

else
{
	PATH
}