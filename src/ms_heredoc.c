/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:40:16 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/15 18:26:18 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ms_fd_manager.h"

void	ms_heredoc_handler(t_fdlst *fdlst, char **env);
void	ms_heredoc_expand(char **str, char **env);
t_list	*ms_heredoc_expand_lst(char *str, char **env);
void	ms_heredoc_expand_str(t_list *lst, char **str);
void	ms_heredoc_clear_lst(t_list **lst);

void	ms_heredoc_handler(t_fdlst *fdlst, char **env)
{
	char	*res;
	char	*tmp;
	char	buf[1024];
	long	pipefd;
	int		r;

	r = 1;
	tmp = ft_calloc(1, 1);
	if (!tmp)
		ms_fd_error("heredoc");
	while (r)
	{
		r = read(0, buf, sizeof(buf) - sizeof(char));
		if (r < 0)
			break ;
		buf[r] = 0;
		if (!ft_strncmp(buf, fdlst->path, ft_strlen(fdlst->path)))
			break ;
		res = ft_strjoin(tmp, buf);
		free(tmp);
		tmp = res;
		if (!res)
			ms_fd_error("heredoc");
	}
	if (fdlst->type == HEREDOC)
		ms_heredoc_expand(&res, env);
	pipe(&pipefd);
	write(pipefd >> 32, res, ft_strlen(res));
	close(pipefd >> 32);
	fdlst->fd = (int)pipefd;
}

void	ms_heredoc_expand(char **str, char **env)
{
	t_list	*lst;

	lst = ms_heredoc_expand_lst(*str, env);
	ms_heredoc_expand_str(lst, str);
	ms_heredoc_clear_lst(&lst);
}

t_list	*ms_heredoc_expand_lst(char *str, char **env)
{
	int		i;
	int		l;
	t_list	*lst;
	char	*name;

	lst = NULL;
	i = -1;
	l = 0;
	while (str && str[++i])
	{
		if (str[i] == '$')
		{
			ft_lstadd_back(&lst, ft_lstnew(ft_substr(str, l, i - l)));
			name = ms_get_name(str);
			ft_lstadd_back(&lst, \
				ft_lstnew(ms_export_get_value(name, env)));
			if (name)
				free (name);
			i += ms_get_name_length((*str));
			l = i;
		}
	}
	return (lst);
}

void	ms_heredoc_expand_str(t_list *lst, char **str)
{	
	int	i;

	if (lst)
	{
		free(*str);
		i = ft_lst_get_list_content_length(lst) + 1;
		*str = malloc(sizeof(char) * (i + 1));
		if (!*str)
			ms_fd_error("heredoc");
		**str = 0;
		while (lst)
		{
			ft_strlcat(*str, lst->content, i);
			lst = lst->next;
		}
	}
}

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
