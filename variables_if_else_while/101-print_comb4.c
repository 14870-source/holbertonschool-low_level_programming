#include <stdio.h>

/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	int first;
	int second;
	int third;

	for (first = 0; first <= 7; first++)
	{
		for (second = first + 1; second <= 8; second++)
		{
			for (third = second + 1; third <= 9; third++)
			{
				putchar(first + '0');
				putchar(second + '0');
				putchar(third + '0');

				if (!(first == 7 && second == 8 && third == 9))
				{
					putchar(',');
					putchar(' ');
				}
			}
		}
	}

	putchar('\n');

	return (0);
}
