#include "main.h"

/**
 * gb_strcat - This is a function that will be used for
 * concatenation of strings
 * @str2: This is the string to append to another
 * @str1: This is the string to be appended to
 * Return: A pointer/address of the added strings
 *
 */

char *gb_strcat(char *str1, const char *str2)
{
	char *result;

	result = str1;
	while (*str1)
	{
		str1++;
	}
	while (*str2)
	{
		*str1++ = *str2++;
	}

	*str1 = '\0';

	return (result);
}
