/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: licohen <licohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:06:51 by licohen           #+#    #+#             */
/*   Updated: 2024/09/02 16:06:52 by licohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wordlen(char const *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	return (i);
}

static int	ft_wordcount(char const *str, char c)
{
	int	i;
	int	w;

	i = 0;
	w = 0;
	while (*str)
	{
		while (*str == c && *str)
			str++;
		i = ft_wordlen(str, c);
		str += i;
		if (i)
			w++;
	}
	return (w);
}

static char	*ft_strndup(char const *str, int n)
{
	int		i;
	char	*dst;

	i = 0;
	dst = malloc(sizeof(char) * (n + 1));
	if (!dst)
		return (NULL);
	while (i < n)
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static void	ft_freedst(char **dst)
{
	int	i;

	i = 0;
	while (dst[i])
	{
		free(dst[i]);
		i++;
	}
	free(dst);
}

char	**ft_split(char const *s, char c)
{
	int		n;
	int		len;
	char	**dst;

	n = 0;
	len = ft_wordcount(s, c);
	dst = malloc(sizeof(char *) * (len + 1));
	if (!dst)
		return (NULL);
	while (n < len)
	{
		while (*s == c)
			s++;
		dst[n] = ft_strndup(s, ft_wordlen(s, c));
		if (!dst[n])
			return (ft_freedst(dst), NULL);
		s += ft_wordlen(s, c);
		n++;
	}
	dst[n] = 0;
	return (dst);
}
