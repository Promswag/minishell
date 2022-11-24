/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_result.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 11:35:53 by aho               #+#    #+#             */
/*   Updated: 2022/11/22 11:30:15 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

void	ms_result_adress(t_tmp *tmp, t_command *cmd)
{
	int	index;

	index = 0;
	while (tmp)
	{
		if (tmp->field == 0 || tmp->field == 5 || tmp->field == 6)
		{
			cmd->args[index] = tmp->str;
			index++;
		}
		tmp = tmp->next;
	}
}

int	ms_result_init_arg(t_tmp *tmp)
{
	int	index;

	index = 0;
	while (tmp)
	{
		if (tmp->field == 0 || tmp->field == 5 || tmp->field == 6)
			index++;
		tmp = tmp->next;
	}
	return (index);
}

void	ms_result_fd(t_command **result, t_tmp *tmp, t_fdlst **fdlst)
{
	t_fdlst	*elem;

	while (tmp)
	{
		if (tmp->field == 1 || tmp->field == 2 || tmp->field == 3 \
			|| tmp->field == 4)
		{
			elem = ms_new_fdlst(tmp->field, tmp->str);
			ms_fdlstadd_back(fdlst, elem);
		}
		else if (tmp->field == 12)
		{
			elem = ms_new_fdlst(HEREDOC_QUOTED, tmp->str);
			ms_fdlstadd_back(fdlst, elem);
		}
		if (tmp->field == 1 || tmp->field == 3 || tmp->field == 12)
			(*result)->fd_in = elem;
		if (tmp->field == 2 || tmp->field == 4)
			(*result)->fd_out = elem;
		tmp = tmp->next;
	}
}

t_command	*ms_result(t_tmp *tmp, t_fdlst **fdlst, char **env)
{
	t_command	*result;
	int			index;

	result = malloc(sizeof(t_command));
	result->fd_in = NULL;
	result->fd_out = NULL;
	index = ms_result_init_arg(tmp);
	result->args = malloc(sizeof(char *) * (index + 1));
	result->args[index] = NULL;
	ms_result_adress(tmp, result);
	ms_result_fd(&result, tmp, fdlst);
	result->path = NULL;
	if (result->args[0] && ms_cmd_is_builtins(result))
		result->path = ms_path_finder(result->args[0], env);
	return (result);
}
