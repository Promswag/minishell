/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:37:29 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/02/28 16:43:15 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ischarset(char c, char *charset)
{
	int	i;

	i = 0;
	while (*(charset + i))
	{
		if (c == *(charset + i))
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		j;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = ft_strlen(s1);
	if (j)
	{
		while (ft_ischarset(*(s1 + i), (char *)set) && i < j)
			i++;
		while (ft_ischarset(*(s1 + j - 1), (char *)set) && i < j)
			j--;
	}
	str = malloc(sizeof(char) * (j - i + 1));
	if (str)
		ft_strlcpy(str, s1 + i, j - i + 1);
	return (str);
}
