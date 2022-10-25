/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 18:35:16 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/02/28 14:07:19 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int	i;
	int	j;
	int	l;

	l = ft_strlen(needle);
	if (l == 0)
		return ((char *)haystack);
	i = -1;
	j = 0;
	while (haystack[++i] && i < (int)len)
	{
		if (needle[j] != haystack[i])
			j = 0;
		if (needle[j] == haystack[i])
			j++;
		if (j == l)
			return ((char *)haystack + i - l + 1);
	}
	return (0);
}
