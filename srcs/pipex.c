/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: licohen <licohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:35:33 by licohen           #+#    #+#             */
/*   Updated: 2024/09/10 19:42:27 by licohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"



void executer(char *cmd, char **envp)
{
    int i;
    char **command;
    char **path;
    char *way;

    command = ft_split(cmd, ' ');
    path = split_path(envp);
    if (!path)
        ft_error("Error");
    // i = 0;
    // while (path[i])
    // {
    //     way = 
    // }
}

void pipex(int argc, char **argv, char **envp)
{
    (void)argv;
    (void)envp;

    int fd[2];
    int pid1;
    int pid2;

    if (argc != 5)
        ft_error("Nombre d'arguments incorrect");
    if (pipe(fd) == -1)
        ft_perror("Error");
    pid1 = fork();
    if (pid1 == -1)
        ft_perror("ERROR");
    if (pid1 == 0) 
    {
        printf("PID1: %d\n", getpid());
        exit(0);
    }
    pid2 = fork();
    if (pid2 == -1)
        ft_perror("ERROR");
    if (pid2 == 0) 
    {
        printf("PID2: %d\n", getpid());
        exit(0);
    }
    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

int main(int argc, char **argv, char **envp)
{
    pipex(argc, argv, envp);
    return 0;
}