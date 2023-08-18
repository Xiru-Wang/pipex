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

