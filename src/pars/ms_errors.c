/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aho <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:56:38 by aho               #+#    #+#             */
/*   Updated: 2022/10/25 15:56:39 by aho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ms_errors(int cmd)
{
	write(2, "minishell: ", 12);
	if (cmd == 1)
		write(2, "\' or \" not ended correctly\n", 28);
	if (cmd == 2)
		write(2, "use of tokens prohibited\n", 26);
	if (cmd == 3)
		write(2, "syntax error\n", 14);
	return (0);
}
