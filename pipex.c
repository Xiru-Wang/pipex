/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiwang <xiwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:02:54 by xiruwang          #+#    #+#             */
/*   Updated: 2023/08/24 19:13:51 by xiwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
//#define BUFFER_SIZE 4096
//./a.out color.txt cat rev file2.txt

//https://github.com/jdecorte-be/42-Pipex/tree/master
//https://codeberg.org/ilshat/Pipex/src/branch/main/My_pipex/pipex.c
//https://github.com/mariadaan/PIPEXaminator

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
		exit (1);
	}
	if (pipe(fd) == -1)
		handle_err("pipe");
	pid = fork();
	if (pid == -1)
		handle_err("fork");
	if (pid == 0)
		child(av, fd, env);
	waitpid(pid, &status, 0);
	parent(av, fd, env);
	close(fd[1]);
	close(fd[0]);
	return (0);
}

/*
dup2(): swap stdin(keyboard) to file1 / swap stdout(screen) to file2
*/
static void	child(char **av, int *fd, char **env)
{
	int	file1;

	file1 = open(av[1], O_RDONLY);
	if (file1 == -1)
		handle_err("Failed to open file1");
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

	file2 = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file2 == -1)
		handle_err("Failed to open file2");
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(file2, STDOUT_FILENO);
	close(file2);
	close(fd[1]);
	call_cmd(av[3], env);
}

/*
cmd[0]:cmd name, cmd[1]: cmd argument eg. char *cmd[] = {"ls", "-l", NULL}
*/

static void	call_cmd(char *av, char **env)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(av, ' ');
	path = get_path(cmd[0], env);
	if (!path)
	{
		write(STDERR_FILENO, "command not found: ", 19);
		write(STDERR_FILENO, cmd[0], ft_strlen(cmd[0]));
		ft_free(cmd);
		exit(127);
	}
	if (execve(path, cmd, env) == -1)
	{
		free(path);
		ft_free(cmd);
		handle_err("execve");
	}
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
	while (ft_strnstr(env[i], "PATH", 4) == NULL)
		i++;
	paths = ft_split(env[i] + 5, ':');
	if (!paths)
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
