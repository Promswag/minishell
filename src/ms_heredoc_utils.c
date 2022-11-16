/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:39:56 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/16 17:40:34 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ms_fd_manager.h"

void	ms_heredoc_clear_lst(t_list **lst);
int		ft_lst_get_list_content_length(t_list *lst);
int		ms_get_name_length(char *str);

void	ms_heredoc_clear_lst(t_list **lst)
{
	t_list	*prev;

	while (*lst)
	{
		prev = *lst;
		*lst = (*lst)->next;
		if (prev->content)
		{
			ft_bzero(prev->content, ft_strlen(prev->content));
			free(prev->content);
		}
		free(prev);
	}
	lst = NULL;
}

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

	i = 0;
	while (str && str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			break ;
		i++;
	}
	return (i);
}
