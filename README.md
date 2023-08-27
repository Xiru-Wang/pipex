# Pipex

This project is about handling pipes.

Your program will be executed as follows: ./pipex file1 cmd1 cmd2 file2

It must take 4 arguments:

file1 and file2 are file names. 

cmd1 and cmd2 are shell commands with their parameters.


# Understand the data flow:

![2](https://github.com/Xiru-Wang/pipex/assets/79924696/3d253c1f-835c-4f63-af84-af0bc96ac338)


# How do pipes facilitate data transfer between processes?

The essence of a pipe is a kernel-level data buffer, not just at the process level. The file descriptors `fd[0]` and `fd[1]` are merely "gateways" or "interfaces" to this buffer.

When a child process writes data to `fd[1]`, the data goes into this kernel-level buffer. When the parent process reads from `fd[0]`, it fetches data from the same kernel buffer.

Here's a simplified breakdown of how this works:

1. **Kernel Buffer**: The pipe created by `pipe()` is actually a data structure or buffer in the kernel. This buffer is independent of any specific process.

2. **File Descriptors as "Gateways"**: The two file descriptors, `fd[0]` and `fd[1]`, can be thought of as two endpoints or "gateways" to this buffer. `fd[1]` is the gateway to write data into the buffer, while `fd[0]` is the gateway to read data from it.

3. **Data Flow**: When the child process writes data to `fd[1]`, the data gets sent to the kernel buffer. When the parent process reads data from `fd[0]`, it fetches from the same kernel buffer.

4. **Process Independence**: File descriptors are independent between processes. So, if the child process closes its `fd[0]`, it doesn't affect the parent's `fd[0]`. However, because both descriptors are "gateways" to the same kernel buffer, data written via one descriptor can be read via the other.

![3](https://github.com/Xiru-Wang/pipex/assets/79924696/8925b1fa-ebaf-451f-bbdb-dc33d17edf3c)

# Environment Variables
![3](https://github.com/Xiru-Wang/pipex/assets/79924696/0e02d81b-9865-45c2-9a36-31c47c48aa0d)

```
#include <stdio.h>
/*
The env parameter is obtained from the operating system
and contains all the environment variables that are set when you start the process.
In fact, when you start a program from the command line, 
it inherits the environment variables from the shell that started it.
*/

int main(int ac, char **av, char **env) 
{
    for (int i = 0; env[i]; i++) {
        printf("%s\n", env[i]);
    }
    return 0;
}
```
# execve() transforms the calling process into a new process.

int execve(const char *path, char *const argv[], char *const envp[]);
- path: the new process file (an executable object file) whose name is pointed to by path
- argv: 2d array(null-terminated),the first element should be the name of the executed program

RETURN VALUES
The successful call has NO process to return to. If execve() does return to the calling process(return value: -1),
an error has occurred; errno is set to indicate the error.
```
#include <unistd.h>
#include <stdio.h>

void call_cmd(char *cmd, char **args)
{
	execve(cmd, args, NULL);
	printf("This line will not be executed, except something went wrong\n");
}

int main()
{
	char cmd[] = "/bin/ls";
	char *args[] = {"ls", "-l", NULL};

	call_cmd(cmd, args);
	printf("if call_cmd sucessful, this line will not be printed out\n");

	return (0);
}
```
# Fork
![4](https://github.com/Xiru-Wang/pipex/assets/79924696/48673432-7052-4314-b9df-b1c5033f6538)

# Dup2
![5](https://github.com/Xiru-Wang/pipex/assets/79924696/89b7edda-dfa4-45ea-b058-4e01be65cba7)
