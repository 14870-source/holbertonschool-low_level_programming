#include "main.h"
#include <stdlib.h>
int main(int argc, char *argv[])
{
	int len1, len2, *result;
	int i, started = 0;

	if (argc != 3)
		print_error();

	if (!_isdigit(argv[1]) || !_isdigit(argv[2]))
		print_error();

	len1 = _strlen(argv[1]);
	len2 = _strlen(argv[2]);

	result = multiply(argv[1], argv[2], len1, len2);

	if (result == NULL)
		return (98);

	for (i = 0; i < len1 + len2; i++)
	{
		if (result[i] != 0)
			started = 1;

		if (started)
			_putchar(result[i] + '0');
	}

	if (!started)
		_putchar('0');

	_putchar('\n');

	free(result);

	return (0);
} 
/**
 * _isdigit - checks if a string contains only digits
 * @s: string
 *
 * Return: 1 if valid, 0 otherwise
 */
int _isdigit(char *s)
{
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (0);
		s++;
	}
	return (1);
}

/**
 * _strlen - returns length of string
 * @s: string
 *
 * Return: length
 */
int _strlen(char *s)
{
	int len = 0;

	while (s[len])
		len++;

	return (len);
}

/**
 * print_error - prints Error and exits
 */
void print_error(void)
{
	char error[] = "Error\n";
	int i;

	for (i = 0; error[i]; i++)
		_putchar(error[i]);

	exit(98);
}
int *multiply(char *num1, char *num2, int len1, int len2)
{
	int i, j;
	int *result;
	int n1, n2, sum;

	result = malloc(sizeof(int) * (len1 + len2));

	if (result == NULL)
		return (NULL);

	for (i = 0; i < len1 + len2; i++)
		result[i] = 0;

	for (i = len1 - 1; i >= 0; i--)
	{
		n1 = num1[i] - '0';

		for (j = len2 - 1; j >= 0; j--)
		{
			n2 = num2[j] - '0';

			sum = n1 * n2 + result[i + j + 1];

			result[i + j + 1] = sum % 10;
			result[i + j] += sum / 10;
		}
	}

	return (result);
}