/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:42:51 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/02/28 14:07:19 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	if (c == 0)
		return ((char *)s + ft_strlen(s));
	i = ft_strlen(s);
	while (--i >= 0)
		if (s[i] == c)
			return ((char *)s + i);
	return (0);
}
