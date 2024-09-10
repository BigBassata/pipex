/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: licohen <licohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:35:41 by licohen           #+#    #+#             */
/*   Updated: 2024/09/10 18:18:22 by licohen          ###   ########.fr       */
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
            path = ft_split(envp[i] + 5, ":");
            return (path);
        }
        i++;
    }
    return (NULL);
}
