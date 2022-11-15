/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_fd_manager.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:46:18 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/15 16:45:44 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_FD_MANAGER_H
# define MS_FD_MANAGER_H

# include "../libft/include/libft.h"

typedef enum e_redir_type
{
	REDIR_IN = 1,
	REDIR_OUT_TRUNCATE,
	REDIT_OUT_APPEND,
	HEREDOC,
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
void			ms_fd_manager(t_fdlst *fdlst, char **env);
void			ms_heredoc_handler(t_fdlst *fdlst, char **env);
void			ms_heredoc_expand(char **str, char **env);
void			ms_fd_error(const char *str);

//	ms_heredoc_utils.c
int				ft_lst_get_list_content_length(t_list *lst);
int				ms_get_name_length(char *str);
char			*ms_get_name(char *str);

#endif