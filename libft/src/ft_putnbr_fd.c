/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:31:00 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/02/28 16:29:18 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_scale(int number, int base)
{
	int	scale;

	scale = 1;
	while (number >= base || number <= -base)
	{
		scale *= base;
		number /= base;
	}
	return (scale);
}

void	ft_putnbr_fd(int n, int fd)
{
	int	scale;

	scale = ft_scale(n, 10);
	if (n < 0)
		ft_putchar_fd('-', fd);
	while (scale != 0)
	{
		if (n >= 0)
			ft_putchar_fd(n / scale + 48, fd);
		else
			ft_putchar_fd(-(n / scale) + 48, fd);
		n %= scale;
		scale /= 10;
	}
}
