#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * copy_file - copies content from one file to another
 * @from: source file descriptor
 * @to: destination file descriptor
 * @name: destination file name
 * Return: 0 on success, 98 or 99 on failure
 */
int copy_file(int from, int to, char *name)
{
	char buffer[1024];
	ssize_t r, w;

	while ((r = read(from, buffer, 1024)) > 0)
	{
		w = write(to, buffer, r);
		if (w != r)
		{
			dprintf(STDERR_FILENO,
				"Error: Can't write to %s\n", name);
			return (99);
		}
	}

	if (r == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't read from file %s\n", name);
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
 * open_source - opens the source file
 * @name: source file name
 * Return: file descriptor or -1
 */
int open_source(char *name)
{
	int fd;

	fd = open(name, O_RDONLY);
	if (fd == -1)
		dprintf(STDERR_FILENO,
			"Error: Can't read from file %s\n", name);

	return (fd);
}

/**
 * open_destination - opens the destination file
 * @name: destination file name
 * Return: file descriptor or -1
 */
int open_destination(char *name)
{
	int fd;

	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd == -1)
		dprintf(STDERR_FILENO,
			"Error: Can't write to %s\n", name);

	return (fd);
}

/**
 * main - copies a file to another file
 * @ac: number of arguments
 * @av: arguments
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	int from, to, result;

	if (ac != 3)
	{
		dprintf(STDERR_FILENO,
			"Usage: cp file_from file_to\n");
		return (97);
	}

	from = open_source(av[1]);
	if (from == -1)
		return (98);

	to = open_destination(av[2]);
	if (to == -1)
	{
		close(from);
		return (99);
	}

	result = copy_file(from, to, av[2]);
	if (result != 0)
	{
		close(from);
		close(to);
		return (result);
	}

	result = close_file(from);
	if (result != 0)
	{
		close(to);
		return (result);
	}

	return (close_file(to));
}
