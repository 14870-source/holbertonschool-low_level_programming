#include "main.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * read_textfile - reads a text file and prints it to standard output
 * @filename: name of the file to read
 * @letters: number of letters to read and print
 * Return: number of letters read and printed, or 0 on failure
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
	int fd;
	ssize_t read_bytes;
	ssize_t write_bytes;
	char *buffer;

	if (filename == NULL)
		return (0);

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);

	buffer = malloc(letters);
	if (buffer == NULL)
	{
		close(fd);
		return (0);
	}

	read_bytes = read(fd, buffer, letters);
	if (read_bytes == -1)
	{
		free(buffer);
		close(fd);
		return (0);
	}

	write_bytes = write(STDOUT_FILENO, buffer, read_bytes);

	free(buffer);
	close(fd);

	if (write_bytes != read_bytes)
		return (0);

	return (read_bytes);
}
