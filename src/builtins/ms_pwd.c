/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:27:29 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/04 14:27:32 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_pwd(t_command cmd, char ***env)
{
	char	path[100];

	(void)cmd;
	getcwd(path, 100);
	if (errno)
		perror("");
	write(1, path, ft_strlen(path));
	write(1, "\n", 1);
	// printf("%s\n", path);
}
