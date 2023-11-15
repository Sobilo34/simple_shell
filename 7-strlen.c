#include "main.h"

/**
 * gb_strlen - Thiis is a function that is used to
 * calculate the number of chars in a string
 * @input: The string to be calculated
 * Return: The value of the calulation
 */

size_t gb_strlen(const char *input)
{
	size_t len = 0;

	if (input == NULL)
	{
		return (0);
	}

	while (input[len])
	{
		len++;
	}

	return (len);
}
