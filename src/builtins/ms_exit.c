/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:04:10 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/21 12:45:03 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static int	ll_overflow_check(const char *str)
{
	int			i;
	long long	r;
	int			sign;

	r = 0;
	sign = 1;
	i = 0;
	while (*(str + i) == '\t' || *(str + i) == '\n' || *(str + i) == '\v'
		|| *(str + i) == '\f' || *(str + i) == '\r' || *(str + i) == ' ')
		i++;
	if (*(str + i) == '+' || *(str + i) == '-')
		if (*(str + i++) == '-')
			sign = -1;
	while (*(str + i) >= 48 && *(str + i) <= 57)
	{
		if (sign == 1 && (r > \
			((long long)0x7FFFFFFFFFFFFFFF - (*(str + i) - 48)) / 10))
			return (-1);
		if (sign == -1 && (r * sign < \
			((long long)0x8000000000000000 + (*(str + i) - 48)) / 10))
			return (-1);
		r = r * 10 + *(str + i) - 48;
		i++;
	}
	return (0);
}

static int	ms_exit_legal(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		while (s[i] == '\t' || s[i] == '\n' || s[i] == '\v' || \
			s[i] == '\f' || s[i] == '\r' || s[i] == ' ')
		i++;
		if (s[i] == '-' || s[i] == '+')
			i++;
		while (s[i])
			if (!ft_isdigit(s[i++]))
				return (0);
	}
	return (1);
}

void	ms_exit(t_command *cmd, char ***env)
{
	(void)env;
	if (!cmd->args[1])
	{
		write(STDERR_FILENO, "exit\n", 5);
		exit(0);
	}
	else
	{
		write(STDERR_FILENO, "exit\n", 5);
		if (ms_exit_legal(cmd->args[1]) && ll_overflow_check(cmd->args[1]) != -1)
		{
			if (cmd->args[2])
			{
				write(STDERR_FILENO, SHELL_NAME, ft_strlen(SHELL_NAME));
				write(STDERR_FILENO, ": exit: too many arguments\n", 27);
			}
			else
				exit(ft_atoi(cmd->args[1]) & 255);
		}
		else
		{
			write(STDERR_FILENO, SHELL_NAME, ft_strlen(SHELL_NAME));
			write(STDERR_FILENO, ": exit: ", 8);
			write(STDERR_FILENO, cmd->args[1], ft_strlen(cmd->args[1]));
			write(STDERR_FILENO, ": numeric argument required\n", 28);
			exit(255);
		}
	}
}
