/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:13:52 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/02/28 16:41:58 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	l;
	char	*str;

	if (!s)
		return (NULL);
	i = 0;
	l = ft_strlen(s);
	if (start > l)
	{
		str = malloc(1);
		if (str)
		{
			str[0] = '\0';
			return (str);
		}
		return (NULL);
	}
	if (start + len > l)
		len = l - start;
	str = malloc(sizeof(char) * (len + 1));
	if (str)
		ft_strlcpy(str, s + start, len + 1);
	return (str);
}
