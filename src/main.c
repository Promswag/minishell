/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:09:44 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/09 16:12:39 by aho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code;

//int	main(void)
//{
//	t_shell	shell;
//	char	*buf;
//
//	shell = shell_init();
//	while (1)
//	{
//		buf = readline("minishell> ");
//		if (!buf)
//		{
//			ft_putstr_fd("\033[A", 1);
//			ft_putstr_fd("minishell> exit\n", 1);
//			break ;
//		}
//		else
//		{
//			ft_putstr_fd(buf, 1);
//			if (*buf != 0)
//				write(1, "\n", 1);
//		}
//	}
//	shell_restore(&shell);
//	return (0);
//}
