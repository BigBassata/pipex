/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: licohen <licohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:35:33 by licohen           #+#    #+#             */
/*   Updated: 2024/09/11 22:48:24 by licohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"


void	executer(char *cmd, char **envp)
{
	int		i;
	char	**command;
	char	**path;
	char	*way;

	command = ft_split(cmd, ' ');
	path = splitting_paths(envp);
	if (path == NULL)
		ft_error("Error: no PATH");
	i = 0;
	while (path[i])
	{
		way = ft_strjoin_mod(path[i], command[0]);
		if (access(way, F_OK) == 0)
		{
			if (execve(way, command, NULL) == -1)
				ft_perror("ERROR");
		}
		free(way);
		i++;
	}
	ft_free(command);
	ft_free(path);
	ft_perror("ERROR");
}

void	first_command_executing(int *fd, char **argv, char **envp)
{
	int	f_in;

	f_in = open(argv[1], O_RDONLY);
	if (f_in < 0)
		ft_perror("ERROR");
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		ft_perror("ERROR");
	if (dup2(f_in, STDIN_FILENO) == -1)
		ft_perror("ERROR");
	close(fd[0]);
	close(f_in);
	close(fd[1]);
	executer(argv[2], envp);
}

void	second_command_executing(int *fd, char **argv, char **envp)
{
	int	f_out;

	f_out = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (f_out < 0)
		ft_perror("ERROR");
	if (dup2(fd[0], STDIN_FILENO) == -1)
		ft_perror("ERROR");
	if (dup2(f_out, STDOUT_FILENO) == -1)
		ft_perror("ERROR");
	close(fd[1]);
	close(f_out);
	close(fd[0]);
	executer(argv[3], envp);
}

void	pipex(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	pid1;
	int	pid2;

	if (argc != 5)
		ft_error("Error: wrong nbr of args");
	if (pipe(fd) == -1)
		ft_perror("ERROR");
	pid1 = fork();
	if (pid1 == -1)
		ft_perror("ERROR");
	if (pid1 == 0)
		first_command_executing(fd, argv, envp);
	pid2 = fork();
	if (pid2 == -1)
		ft_perror("ERROR");
	if (pid2 == 0)
		second_command_executing(fd, argv, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int main(int argc, char **argv, char **envp)
{
    pipex(argc, argv, envp);
    return (0);
}