/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: licohen <licohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:35:33 by licohen           #+#    #+#             */
/*   Updated: 2024/09/10 21:32:07 by licohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// void executer(char *cmd, char **envp)
// {
//     int i;
//     char **command;
//     char **path;
//     char *way;

//     command = ft_split(cmd, ' ');
//     path = split_path(envp);
//     if (!path)
//         ft_error("Error12");
//     i = 0;
//     while (path[i])
//     {
//         way = ft_path_join(path[i], '/', command[0]);
//         if (access(way, F_OK) == 0)
//         {
//             if (execve(way, command, NULL) == -1)
//                 ft_perror("ERROR11");
//         }
//         free(way);
//         i++;
//     }
//     ft_free(command);
//     ft_free(path);
//     ft_perror("ERROR10");
// }

void executer(char *cmd, char **envp)
{
    char **command;
    char **path;
    char *way;

    command = ft_split(cmd, ' ');
    if (!command) {
        ft_error("Failed to split command");
    }

    path = split_path(envp);
    if (!path) {
        ft_free(command);
        ft_error("Error12: PATH not found");
    }

    for (int i = 0; path[i]; i++) {
        way = ft_path_join(path[i], '/', command[0]);
        if (!way) continue;

        if (access(way, F_OK | X_OK) == 0) {
            execve(way, command, envp);
            ft_perror("ERROR11: execve failed");  // execve only returns on error
        }
        free(way);
    }
    ft_free(command);
    ft_free(path);
    ft_error("ERROR10: Command not found");
}

void first_command_exec(int *fd, char **argv, char **envp)
{
    int file_in;
    
    file_in = open(argv[1], O_RDONLY);
    if (file_in < 0)
        ft_perror("ERROR9");
    if (dup2(fd[1], STDOUT_FILENO) == -1)
        ft_perror("ERROR8");
    if (dup2(file_in, STDIN_FILENO) == -1)
        ft_perror("ERROR7");
    close(fd[0]);
    close(file_in);
    close(fd[1]);
    executer(argv[2], envp);
}


void second_command_exec(int *fd, char **argv, char **envp)
{
    int file_out;
    
    file_out = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
    if (file_out < 0)
        ft_perror("ERROR6");
    if (dup2(fd[1], STDIN_FILENO) == -1)
        ft_perror("ERROR5");
    if (dup2(file_out, STDOUT_FILENO) == -1)
        ft_perror("ERROR4");
    close(fd[1]);
    close(file_out);
    close(fd[0]);
    executer(argv[3], envp);
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
        ft_perror("Error3");
    pid1 = fork();
    if (pid1 == -1)
        ft_perror("ERROR2");
    if (pid1 == 0) 
        first_command_exec(fd, argv, envp);
    pid2 = fork();
    if (pid2 == -1)
        ft_perror("ERROR1");
    if (pid2 == 0) 
        second_command_exec(fd, argv, envp);
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