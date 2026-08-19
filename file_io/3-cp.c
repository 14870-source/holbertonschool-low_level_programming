#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * copy_file - copies the content of one file to another
 * @fd_from: source file descriptor
 * @fd_to: destination file descriptor
 * @file_to: destination file name
 * Return: 0 on success, 98 or 99 on failure
 */
int copy_file(int fd_from, int fd_to, char *file_to)
{
	char buffer[1024];
	ssize_t read_bytes;
	ssize_t write_bytes;

	while ((read_bytes = read(fd_from, buffer, 1024)) > 0)
	{
		write_bytes = write(fd_to, buffer, read_bytes);

		if (write_bytes != read_bytes)
		{
			dprintf(STDERR_FILENO,
				"Error: Can't write to %s\n", file_to);
			return (99);
		}
	}

	if (read_bytes == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't read from file %s\n", file_to);
		return (98);
	}

	return (0);
}

/**
 * close_file - closes a file descriptor
 * @fd: file descriptor
 * Return: 0 on success, 100 on failure
 */
int close_file(int fd)
{
	if (close(fd) == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't close fd %d\n", fd);
		return (100);
	}

	return (0);
}

/**
 * main - copies the content of one file to another
 * @ac: number of arguments
 * @av: arguments
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	int fd_from;
	int fd_to;
	int result;

	if (ac != 3)
	{
		dprintf(STDERR_FILENO,
			"Usage: cp file_from file_to\n");
		return (97);
	}

	fd_from = open(av[1], O_RDONLY);
	if (fd_from == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't read from file %s\n", av[1]);
		return (98);
	}

	fd_to = open(av[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd_to == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't write to %s\n", av[2]);
		close(fd_from);
		return (99);
	}

	result = copy_file(fd_from, fd_to, av[2]);
	if (result != 0)
	{
		close(fd_from);
		close(fd_to);
		return (result);
	}

	result = close_file(fd_from);
	if (result != 0)
	{
		close(fd_to);
		return (result);
	}

	result = close_file(fd_to);
	if (result != 0)
		return (result);

	return (0);
}
