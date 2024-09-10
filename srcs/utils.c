/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: licohen <licohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:35:41 by licohen           #+#    #+#             */
/*   Updated: 2024/09/10 21:12:44 by licohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char **split_path(char **envp)
{
    int i;
    char **path;

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

char *ft_path_join(char const *s1, char connector, char const *s2)
{
    char *str;
    size_t i;
    size_t j;

    if (s1 || s2)
        return (NULL);
    str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
    if (!str)
        return (NULL);
    i = 0;
    j = 0;
    while (s1[j])
    {
        str[i] = s1[j];
        i++;
        j++;
    }  
    str[i] = connector;
    j = 0;
    while (s2[j])
    {
        str[i] = s2[j];
        i++;
        j++;
    }
    str[i] = '\0';
    return (str);
}

void ft_free(char **str)
{
    int i;
    
    i = 0;
    while (str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}