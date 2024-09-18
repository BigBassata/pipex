/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: licohen <licohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:35:54 by licohen           #+#    #+#             */
/*   Updated: 2024/09/11 22:51:39 by licohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <errno.h>
# include <string.h>
# include <sys/wait.h>

void	pipex(int argc, char **argv, char **envp);
void	first_command(int *fd, char **argv, char **envp);
void	second_command(int *fd, char **argv, char **envp);
void	executer(char *cmd, char **envp);

char	**splitting_paths(char **envp);
char	*ft_strjoin_mod(char const *s1, char const *s2);

#endif