/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:45:49 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/02/28 14:07:19 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	l;

	i = ft_strlen(dst);
	l = ft_strlen(src);
	if (dstsize < i)
		l += dstsize;
	else
		l += i;
	j = 0;
	while (src[j] && i + 1 < dstsize)
		dst[i++] = src[j++];
	if (dstsize >= i)
		dst[i] = '\0';
	return (l);
}
