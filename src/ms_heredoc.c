/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:40:16 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/25 10:53:53 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ms_fd_manager.h"
#include <sys/ioctl.h>

int		ms_heredoc_handler(t_fdlst *fdlst, t_shell *shell);
int		ms_heredoc_read_stdin(t_fdlst *fdlst, char **str);
t_list	*ms_heredoc_expand_lst(char *str, char **env);
void	ms_heredoc_if_handler(t_list **lst, char *str, int *i, char **env);
void	ms_heredoc_expand_str(t_list *lst, char **str);

int	ms_heredoc_handler(t_fdlst *fdlst, t_shell *shell)
{
	char	*str;
	long	pipefd;
	t_list	*lst;

	ms_signal_setup(2);
	lst = NULL;
	str = ft_calloc(1, 1);
	if (!str || pipe((int *)&pipefd) || ms_heredoc_read_stdin(fdlst, &str))
		return (1);
	if (fdlst->type == HEREDOC)
	{
		lst = ms_heredoc_expand_lst(str, shell->env);
		ms_heredoc_expand_str(lst, &str);
		ms_heredoc_clear_lst(&lst);
	}
	ioctl(pipefd >> 32, FIONBIO, (int *)1);
	write(pipefd >> 32, str, ft_strlen(str));
	free(str);
	close(pipefd >> 32);
	fdlst->fd = (int)pipefd;
	ms_signal_setup(1);
	return (0);
}

int	ms_heredoc_read_stdin(t_fdlst *fdlst, char **str)
{
	char	buf[1024];
	char	*tmp;
	int		r;

	r = 1;
	while (r)
	{
		write(STDOUT_FILENO, "🐐 ", ft_strlen("🐐 "));
		r = read(0, buf, sizeof(buf) - sizeof(char));
		if (r < 0)
			return (0);
		buf[r] = 0;
		if (!ft_strncmp(buf, fdlst->path, ft_strlen(fdlst->path)) \
			&& buf[ft_strlen(fdlst->path)] == '\n')
			break ;
		tmp = *str;
		*str = ft_strjoin(*str, buf);
		free(tmp);
	}
	return (0);
}

t_list	*ms_heredoc_expand_lst(char *str, char **env)
{
	int		i;
	int		l;
	t_list	*lst;

	lst = NULL;
	i = -1;
	l = 0;
	while (str && str[++i])
	{
		if (str[i] == '$')
		{
			ft_lstadd_back(&lst, ft_lstnew(ft_substr(str, l, i - l)));
			ms_heredoc_if_handler(&lst, str, &i, env);
			l = i + 1;
		}
		if (str[i + 1] == '\0')
			ft_lstadd_back(&lst, ft_lstnew(ft_substr(str, l, i - l + 1)));
	}
	return (lst);
}

void	ms_heredoc_if_handler(t_list **lst, char *str, int *i, char **env)
{
	char	*name;

	if (str[*i + 1] == '?' && ++(*i))
	{
		ft_lstadd_back(lst, ft_lstnew(ft_itoa(g_g.exitcode)));
		g_g.exitcode = 0;
	}
	else if ((str[*i + 1] == '\n' || str[*i + 1] == ' '))
		ft_lstadd_back(lst, ft_lstnew(ft_strdup("$")));
	else if (str[*i + 1] == '$' && ++(*i))
		ft_lstadd_back(lst, ft_lstnew(ft_strdup("")));
	else
	{
		name = ft_substr(str + *i + 1, 0, ms_get_name_length(str + *i + 1));
		ft_lstadd_back(lst, ft_lstnew(ms_export_get_value(name, env)));
		if (name)
			free (name);
		*i += ms_get_name_length((str + *i + 1));
	}
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
			ms_error("heredoc");
		**str = 0;
		while (lst)
		{
			if (lst->content)
				ft_strlcat(*str, lst->content, i);
			lst = lst->next;
		}
	}
}
