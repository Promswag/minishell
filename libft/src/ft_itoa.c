/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:33:20 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/02/28 16:36:09 by gbaumgar         ###   ########.fr       */
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

static int	ft_nblen(int number, int base)
{
	int	len;

	len = 1;
	if (number < 0)
		len++;
	while (number >= base || number <= -base)
	{
		number /= base;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		scale;
	int		i;

	str = malloc(sizeof(char) * (ft_nblen(n, 10) + 1));
	if (!str)
		return (NULL);
	i = 0;
	if (n < 0)
		*(str + i++) = '-';
	scale = ft_scale(n, 10);
	while (scale != 0)
	{
		if (n >= 0)
			*(str + i++) = n / scale + 48;
		else
			*(str + i++) = -(n / scale) + 48;
		n %= scale;
		scale /= 10;
	}
	*(str + i) = '\0';
	return (str);
}
