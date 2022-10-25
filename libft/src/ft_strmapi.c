/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:54:02 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/02/28 15:46:13 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	int				l;
	char			*str;

	i = -1;
	if (s && f)
	{
		l = ft_strlen(s);
		str = malloc(sizeof(char) * (l + 1));
		if (str)
		{
			while (*(s + ++i))
				*(str + i) = (*f)(i, *(s + i));
			*(str + i) = '\0';
		}
		return (str);
	}
	return (NULL);
}
