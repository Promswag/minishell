/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:39:56 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/15 15:42:16 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lst_get_list_content_length(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		if (lst->content)
			i += ft_strlen(lst->content);
		lst = lst->next;
	}
	return (i);
}

int	ms_get_name_length(char *str)
{
	int	i;

	i = 1;
	if (*str != '$')
		return (-1);
	while (*++str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			break ;
		i++;
	}
	return (i);
}

char	*ms_get_name(char *str)
{
	int	i;

	i = ms_get_name_length(str);
	if (i < 0)
		return (NULL);
	return (ft_substr(str, 0, i));
}
