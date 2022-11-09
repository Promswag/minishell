/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:04:10 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/11/04 14:07:43 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	ll_overflow_check(const char *str)
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

int	ms_exit_legal(char *s)
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

int	ms_exit(t_command cmd, char ***env)
{
	if (!cmd.args)
		exit(0);
	else
	{
		write(cmd.err_fd, "exit\n", 5);
		if (ms_exit_legal(cmd.args[0]) && ll_overflow_check(cmd.args[0]) != -1)
		{
			if (cmd.args[1])
			{
				write(cmd.err_fd, SHELL_NAME, ft_strlen(SHELL_NAME));
				write(cmd.err_fd, ": exit: too many arguments\n", 27);
			}
			else
				exit(ft_atoi(cmd.args[0]) & 255);
		}
		else
		{
			write(cmd.err_fd, SHELL_NAME, ft_strlen(SHELL_NAME));
			write(cmd.err_fd, ": exit: ", 8);
			write(cmd.err_fd, cmd.args[0], ft_strlen(cmd.args[0]));
			write(cmd.err_fd, ": numeric argument required\n", 28);
			exit(255);
		}
	}
}
