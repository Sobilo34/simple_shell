#include "main.h"

/**
 * gb_strdup - Duplicate a string.
 * @input: The string to be duplicated.
 * Return: A duplicated string or NULL on failure.
 */
char *gb_strdup(const char *input)
{
	char *new_str;
	size_t len, a;

	if (input == NULL)
	{
		return (NULL);
	}

	len = gb_strlen(input) + 1;
	new_str = (char *)malloc(len * sizeof(char));

	if (new_str == NULL)
		return (NULL);

	a = 0;
	while (input[a] != '\0')
	{
		new_str[a] = input[a];
		a++;
	}
	new_str[a] = '\0';

	return (new_str);
}

