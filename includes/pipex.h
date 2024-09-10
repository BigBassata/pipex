/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: licohen <licohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:35:54 by licohen           #+#    #+#             */
/*   Updated: 2024/09/10 21:11:56 by licohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>
# include "../libft/libft.h"

void    pipex(int argc, char **argv, char **envp);
char    **split_path(char **envp);
void    first_command_exec(int *fd, char **argv, char **envp);
void    second_command_exec(int *fd, char **argv, char **envp);
char    *ft_path_join(char const *s1, char connector, char const *s2);
void    ft_free(char **str);

#endif
