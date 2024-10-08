/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: licohen <licohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:35:33 by licohen           #+#    #+#             */
/*   Updated: 2024/09/24 16:48:25 by licohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	try_execute(char **command, char *path)
{
	char	*way;

	way = ft_strjoin_mod(path, command[0]);
	if (access(way, X_OK) == 0)
	{
		if (execve(way, command, NULL) == -1)
		{
			ft_free(command);
			ft_perror("ERROR");
		}
	}
	free(way);
}

static void	execute_with_path(char **command, char **path)
{
	int	i;

	i = 0;
	while (path[i])
		try_execute(command, path[i++]);
	ft_free(command);
	ft_free(path);
	ft_perror("ERROR");
}

void	executer(char *cmd, char **envp)
{
	char	**command;
	char	**path;

	command = ft_split(cmd, ' ');
	if (!command)
		ft_perror("ERROR");
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (access(command[0], X_OK) == 0)
		{
			if (execve(command[0], command, NULL) == -1)
			{
				ft_free(command);
				ft_perror("ERROR");
			}
		}
		ft_perror("ERROR");
	}
	path = splitting_paths(envp);
	if (path == NULL)
		ft_perror("ERROR");
	execute_with_path(command, path);
}

void	first_command(int *fd, char **argv, char **envp)
{
	int	f_in;

	f_in = open(argv[1], O_RDONLY);
	if (f_in < 0)
	{
		close(fd[0]);
		close(fd[1]);
		ft_perror("ERROR");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		ft_perror("ERROR");
		exit(EXIT_FAILURE);
	}
	if (dup2(f_in, STDIN_FILENO) == -1)
		ft_perror("ERROR");
	close(fd[0]);
	close(f_in);
	close(fd[1]);
	executer(argv[2], envp);
}

void	second_command(int *fd, char **argv, char **envp)
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
	
	(void) argc;
	if (pipe(fd) == -1)
		ft_perror("ERROR");
	pid1 = fork();
	if (pid1 == -1)
	{
		close(fd[0]);
		close(fd[1]);
		ft_perror("ERROR");
	}
	if (pid1 == 0)
		first_command(fd, argv, envp);
	pid2 = fork();
	if (pid2 == -1)
		ft_perror("ERROR");
	if (pid2 == 0)
		second_command(fd, argv, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
