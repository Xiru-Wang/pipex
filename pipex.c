/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiruwang <xiruwang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:02:54 by xiruwang          #+#    #+#             */
/*   Updated: 2023/08/25 19:56:51 by xiruwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#define BUFFER_SIZE 4096
//./a.out color.txt cat rev file2.txt

//https://github.com/jdecorte-be/42-Pipex/tree/master
//https://codeberg.org/ilshat/Pipex/src/branch/main/My_pipex/pipex.c
//https://github.com/mariadaan/PIPEXaminator

static void	child(char **av, int *fd, char **env);
static void	parent(char **av, int *fd, char **env);
static int	call_cmd(char *av, char **env);
static char	*get_path(char *cmd, char **env);

int	main(int ac, char **av, char **env)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	if (ac != 5)
	{
		write(2, "./pipex file1 cmd1 cmd2 file2\n", 31);
		exit (1);
	}
	if (pipe(fd) == -1)
		handle_err("pipe");
	pid = fork();
	if (pid == -1)
		handle_err("fork");
	if (pid == 0)
		child(av, fd, env);
	waitpid(pid, &status, WNOHANG);//waitpid(pid, &status, 0);
	parent(av, fd, env);
}

/*
dup2(): redirect stdin(keyboard) to file1 / swap stdout(screen) to file2
*/
static void	child(char **av, int *fd, char **env)
{
	int	file1;

	file1 = open(av[1], O_RDONLY);
	if (file1 == -1)
		handle_err("pipex: input");
	dup2(file1, STDIN_FILENO);
	close(file1);
	dup2(fd[1], STDOUT_FILENO);
	close_pipe(fd);
	call_cmd(av[2], env);
}

/*
-rw-r--r--/0644 (default permission), cmd line "ls -l" to check
*/

static void	parent(char **av, int *fd, char **env)
{
	int		file2;
	char	*buffer;
	ssize_t	bytes_read;
	int		input;
	int		output;

	file2 = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file2 == -1)
		handle_err("pipex: output");
	input = dup2(fd[0], STDIN_FILENO);
	output = dup2(file2, STDOUT_FILENO);
	close(file2);
	close_pipe(fd);
	if (call_cmd(av[3], env) == 1)
	{
		buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		bytes_read = read(input, buffer, BUFFER_SIZE);
		if (bytes_read > 0)
			write(output, buffer, bytes_read);
		free(buffer);
	}
}

/*
cmd[0]:cmd name, cmd[1]: cmd argument eg. char *cmd[] = {"ls", "-l", NULL}
*/

static int	call_cmd(char *av, char **env)
{
	char	**cmd;
	char	*path;

	if (ft_strnstr(av, "awk ", 4) != NULL)
	{
		cmd = call_awk(av);
		if (cmd == NULL)
			return (1);
	}
	else
		cmd = ft_split(av, ' ');
	path = get_path(cmd[0], env);
	if (!path)
	{
		write(STDERR_FILENO, "pipex: ", 7);
		write(STDERR_FILENO, cmd[0], ft_strlen(cmd[0]));
		write(STDERR_FILENO, ": command not found\n ", 20);
		ft_free(cmd);
		exit(1);//127?
	}
	if (execve(path, cmd, env) == -1)
	{
		free(path);
		ft_free(cmd);
		handle_err("execve");
	}
	return (0);
}

/*
1. loop thru all enviroment vars
2. find path= eg. PATH=/bin:/usr/bin:/usr/local/bin
3. skip "path="
4. Got all paths:(PATH=)/bin:/usr/bin:/usr/local/bin
5. strjoin "/" + "cmd name"
6. access, try one by one
*/

static char	*get_path(char *cmd, char **env)
{
	char	**paths;
	char	*path_dir;
	char	*path_cmd;
	int		i;

	i = 0;
	while (ft_strnstr(env[i], "PATH=", 5) == NULL)
		i++;
	paths = ft_split(env[i] + 5, ':');
	if (paths == NULL)
		handle_err("No path found");
	i = 0;
	while (paths[i])
	{
		path_dir = ft_strjoin(paths[i], "/");
		path_cmd = ft_strjoin(path_dir, cmd);
		free(path_dir);
		if (access(path_cmd, F_OK | X_OK) == 0)
		{
			ft_free(paths);
			return (path_cmd);
		}
		free(path_cmd);
		i++;
	}
	ft_free (paths);
	return (NULL);
}
