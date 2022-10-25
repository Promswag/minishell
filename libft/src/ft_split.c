/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:57:32 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/02/28 16:43:37 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ischarset(char c, char charset)
{
	if (c == '\0')
		return (1);
	if (c == charset)
		return (1);
	return (0);
}

static int	ft_countwords(const char *str, char sep)
{
	int	i;
	int	wordcount;

	wordcount = 0;
	i = -1;
	while (*(str + ++i))
		if (!ft_ischarset(*(str + i), sep) && ft_ischarset(*(str + i + 1), sep))
			wordcount++;
	return (wordcount);
}

static int	ft_wordlength(const char *str, char sep)
{
	int	i;

	i = 0;
	while (!ft_ischarset(*(str + i), sep))
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		wordcount;
	int		i;

	if (!s)
		return (NULL);
	wordcount = ft_countwords(s, c);
	tab = malloc(sizeof(char *) * (wordcount + 1));
	if (!tab)
		return (NULL);
	*(tab + wordcount) = NULL;
	i = -1;
	while (++i < wordcount)
	{
		while (ft_ischarset(*s, c))
			s++;
		*(tab + i) = malloc(sizeof(char) * (ft_wordlength(s, c) + 1));
		if (!tab)
			return (NULL);
		ft_strlcpy(*(tab + i), s, ft_wordlength(s, c) + 1);
		s += ft_wordlength(s, c);
	}
	return (tab);
}
