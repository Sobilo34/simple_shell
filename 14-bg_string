#include "main.h"

/**
 * _putchar - This function writes the character x to stdout
 * @x: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char x)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (x == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(1, buf, a);
		a = 0;
	}
	if (x != BUF_FLUSH)
		buf[a++] = x;
	return (1);
}

/**
 *_puts - This function prints an input string
 *@str: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	int a = 0;

	if (!str)
		return;
	while (str[a] != '\0')
	{
		_putchar(str[a]);
		a++;
	}
}
