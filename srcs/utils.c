/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: licohen <licohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:35:41 by licohen           #+#    #+#             */
/*   Updated: 2024/09/11 22:46:42 by licohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**splitting_paths(char **envp)
{
	int		i;
	char	**path;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			path = ft_split(envp[i] + 5, ':');
			return (path);
		}
		i++;
	}
	return (NULL);
}

// char	*ft_strjoin_mod(char const *s1, char connector, char const *s2)
// {
// 	char	*str;
// 	size_t	i;
// 	size_t	j;

// 	if (!s1 || !s2)
// 		return (NULL);
// 	str = (char *) malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (s1[j])
// 		str[i++] = s1[j++];
// 	str[i++] = connector;
// 	j = 0;
// 	while (s2[j])
// 		str[i++] = s2[j++];
// 	str[i] = '\0';
// 	return (str);
// }

char	*ft_strjoin_mod(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	str = (char *) malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		str[i++] = s1[j++];
	str[i++] = '/';
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}


