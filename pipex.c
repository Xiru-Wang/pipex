/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiwang <xiwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:02:54 by xiruwang          #+#    #+#             */
/*   Updated: 2023/08/23 20:33:41 by xiwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#define BUFFER_SIZE 4096
//./a.out color.txt cat rev file2.txt

//https://github.com/jdecorte-be/42-Pipex/tree/master
//https://codeberg.org/ilshat/Pipex/src/branch/main/My_pipex/pipex.c

static	void	child(char **av, int *fd, char **env);
static	void	parent(char **av, int *fd, char **env);
static	void	call_cmd(char *av, char **env);
static	char	*get_path(char *cmd, char **env);

int	main(int ac, char **av, char **env)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	if (ac != 5)
	{
		write(2, "./pipex file1 cmd1 cmd2 file2\n", 31);
		return (1);
	}
	if (pipe(fd) == -1)
	{
		perror("Pipe");
		return (1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Fork");
		return (1);
	}
	if (pid == 0)
		child(av, fd, env);
	waitpid(pid, &status, 0);
	parent(av, fd, env);
	close(fd[1]);
	close(fd[0]);
	return(0);
}

/*
dup2(): swap stdin(keyboard) to file1 / swap stdout(screen) to file2
*/
static void	child(char **av, int *fd, char **env)
{
	int	file1;

	file1 = open(av[1], O_RDONLY);
	if (file1 == -1)
	{
		perror("Failed to open the file");
		exit(1);
	}
	dup2(file1, STDIN_FILENO);
	close(file1);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	close(fd[0]);
	call_cmd(av[2], env);
}

/*always close the end of the pipe you don't use,
as long as the pipe is open, the other end will
be waiting for input and will not be able to finish its process*/

/*
-rw-r--r--/0644 (default permission), cmd line "ls -l" to check
*/
static void	parent(char **av, int *fd, char **env)
{
	int	file2;
	//char buffer[BUFFER_SIZE];
	//ssize_t bytes_read;

	file2 = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file2 == -1)
	{
		perror("Failed to open the file2");
		exit(EXIT_FAILURE);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(file2, STDOUT_FILENO);
	close(fd[1]);
	call_cmd(av[3], env);
	// close(fd[0]);
	// close(file2);
	// exit(0);
}

/*
	if (call_cmd(av[3], env) == 1)
	{
		while ((bytes_read = read(fd[0], buffer, BUFFER_SIZE)) > 0)
			write(file2, buffer, bytes_read);
	}
*/

/*
cmd[0]:cmd name, cmd[1]: cmd argument eg. char *cmd[] = {"ls", "-l", NULL}
*/
static void	call_cmd(char *av, char **env)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(av, ' ');
	path = get_path(cmd[0], env);
	printf("%s\n", path);
	printf("%s\n", cmd[0]);
	if (cmd && path)
	{
		if (execve(path, cmd, env) == -1)
		{
			perror("Command not found");
			ft_free(cmd);
			free(path);
			exit(1);
		}
	}
	else
	{
		free(path);
		ft_free(cmd);
		perror("Error");
		exit(1);
	}
	exit(0);
}


/*
	if (ft_strnstr(av, "awk ", 4) != NULL)
	{
		cmd = (char **)malloc(3 * sizeof(char *));
		cmd[0] = ft_strdup("awk");
		int len = ft_strlen(av);
		if (av[5] && (av[5] == '{') && av[4] == av[len - 1])
		{
			i = 5;
			int k = 0;
			cmd[1] = (char *)malloc(sizeof(char) * (len - 4));
			while (av[i] && av[i] != '\'' && av[i] != '\"')
				cmd[1][k++] = av[i++];
			cmd[1][k] = 0;
			cmd[2] = NULL;
		}
		else if (av[5] == '\'')
		{
			ft_free(cmd);
			perror("awk: syntax error");
			exit(2);
		}
		else if (av[5] == '\"')
		{
			ft_free(cmd);
			return(1);
		}
	}
*/
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
