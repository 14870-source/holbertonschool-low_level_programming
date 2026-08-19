#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * main - copies the content of one file to another
 * @ac: number of arguments
 * @av: arguments
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	int fd_from, fd_to;
	int close_from, close_to;
	ssize_t read_bytes, write_bytes;
	char buffer[1024];

	if (ac != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		return (97);
	}

	fd_from = open(av[1], O_RDONLY);
	if (fd_from == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", av[1]);
		return (98);
	}

	fd_to = open(av[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd_to == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", av[2]);
		close(fd_from);
		return (99);
	}

	while ((read_bytes = read(fd_from, buffer, 1024)) > 0)
	{
		write_bytes = write(fd_to, buffer, read_bytes);

		if (write_bytes != read_bytes)
		{
			dprintf(STDERR_FILENO,
				"Error: Can't write to %s\n", av[2]);
			close(fd_from);
			close(fd_to);
			return (99);
		}
	}

	if (read_bytes == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", av[1]);
		close(fd_from);
		close(fd_to);
		return (98);
	}

	close_from = close(fd_from);
	if (close_from == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't close fd %d\n", fd_from);
		return (100);
	}

	close_to = close(fd_to);
	if (close_to == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't close fd %d\n", fd_to);
		return (100);
	}

	return (0);
}
