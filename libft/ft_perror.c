/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: licohen <licohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:22:24 by licohen           #+#    #+#             */
/*   Updated: 2024/09/11 19:02:39 by licohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	ft_perror(char *str)
// {
// 	perror(str);
// 	exit(EXIT_FAILURE);
// }

void ft_perror(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}