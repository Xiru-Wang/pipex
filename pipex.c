#include <unistd.h>//fork pipe access
#include <fcntl.h>//open  int open(const char *path, int oflag, ...);
#include <stdio.h>//perror
//https://github.com/jdecorte-be/42-Pipex/tree/master
//https://codeberg.org/ilshat/Pipex/src/branch/main/My_pipex/pipex.c
//pipe() takes an array of two int such as int end[2], and links them together.
//end[1] will write to the its own fd, and end[0]
//will read end[1]’s fd and write to its own

// void	pipex(int f1, int f2, char *cmd1, char *cmd2)
// {
// 	int		fd[2];
// 	pid_t	pid;

// 	pipe(fd);
// 	pid = fork();
// 	if (pid < 0)
// 	{
// 		perror("fork failed");
// 		return (1);
// 	}
// 	if (pid == 0)
// 		child(f1, cmd1);
// 	else
// 		parent(f2, cmd2);
// }

//int dup2(int fd1, int fd2) [swap]
//it will close fd2 and duplicate the value of fd2 to fd1

int	main(int ac, char **av, char **envp)
{
	pid_t	pid;//process id
	int		fd[2];

	if (ac == 5)
	{
		if (pipe(fd) == -1)
		{
			perror("Pipe error");
			exit(1);//exit or return?
		}
		pid = fork(); // pid_t fork(void);
		if (pid < 0)// == -1
		{
			perror("Fork failed");//void perror(const char *s);"string: errno"
			exit (1);
		}
		if (pid == 0)//child
			child(av, envp, fd);
		parent(av, envp, fd);
		close(fd[1]);
		close(fd[0]);
	}
	return (0);
}

//int access(char *pathname. int mode)
//F_OK existence R_OK W_OK X_OK read, write, execute
void	child(char **av, char **envp, int *fd)
{
	if (access(av[1], F_OK) != 0)// if file does not exist
	{
		write(2, "No such file or directory\n", 32);
		exit(1);
	}
	if (access(av[1], R_OK) != 0)
	{
		write(2, "Permission denied\n", 32);
		exit(1);
	}
	dup2(fd[1], 1); //swap stdout to fd[1] why not stdin first??
	dup2(open(av[1], O_RDONLY), 0);//swap stdin to infile
	close(fd[0]);//wait for parent to read
	call_cmd(av[2], envp);
}
/*always close the end of the pipe you don't use,
as long as the pipe is open, the other end will
be waiting for input and will not be able to finish its process*/

void	parent(char **av, char **envp, int *fd)
{
	int	fd;

	fd = open(av[4], O_WRONLY....); // if file doesnt exist or renew
	if (fd == -1)
	{
		perror("Open failed");
		exit(1);
	}
	dup2(fd[0], 0);
	dup2(fd, 1);
	close(fd[1]);// child write
	call_cmd(av[3], envp);
}
