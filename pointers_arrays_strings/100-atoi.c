#include "main.h"

/**
 * _atoi - converts a string to an integer
 * @s: string to convert
 *
 * Return: integer value
 */
int _atoi(char *s)
{
	int i = 0;
	int sign = 1;
	int result = 0;

	while (s[i] != '\0')
	{
		if (s[i] == '-')
			sign *= -1;

		else if (s[i] >= '0' && s[i] <= '9')
			break;

		i++;
	}

	while (s[i] >= '0' && s[i] <= '9')
	{
		if (sign == -1)
			result = (result * 10) - (s[i] - '0');
		else
			result = (result * 10) + (s[i] - '0');

		i++;
	}

	return (result);
}
