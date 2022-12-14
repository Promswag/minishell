/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_fd_manager.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:46:18 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/25 11:15:48 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_FD_MANAGER_H
# define MS_FD_MANAGER_H

# include "minishell.h"

typedef struct s_shell	t_shell;

typedef enum e_redir_type
{
	REDIR_IN = 1,
	REDIR_OUT_TRUNCATE,
	HEREDOC,
	REDIR_OUT_APPEND,
	HEREDOC_QUOTED
}	t_redir_type;

typedef struct s_fdlst
{
	int				fd;
	int				type;
	char			*path;
	struct s_fdlst	*next;
}	t_fdlst;

//	ms_fd_manager.c
int			ms_fd_manager(t_fdlst *fdlst, t_shell *shell);
void		ms_fd_close(t_fdlst *fdlst);

//	ms_heredoc.c
int			ms_heredoc_handler(t_fdlst *fdlst, t_shell *shell);
int			ms_heredoc_read_stdin(t_fdlst *fdlst, char **str);
t_list		*ms_heredoc_expand_lst(char *str, char **env);
void		ms_heredoc_if_handler(t_list **lst, char *str, int *i, char **env);
void		ms_heredoc_expand_str(t_list *lst, char **str);

//	ms_heredoc_utils.c
void		ms_heredoc_clear_lst(t_list **lst);
int			ms_get_name_length(char *str);
int			ft_lst_get_list_content_length(t_list *lst);

#endif