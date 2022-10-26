/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aho <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:28:23 by aho               #+#    #+#             */
/*   Updated: 2022/10/25 14:28:24 by aho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	main(void)
{
	char *buff;

	printf("minishell$ ");
	buff = readline(NULL);
	ms_parsing(buff);
	free(buff);
	return 0;
}

t_command	*ms_parsing(char *buff)
{
	t_command	*result;

	result = NULL;
	if(!(ms_syntaxe(buff)))
	{
		result = NULL;
		return (0);
	}
	return (result);
}