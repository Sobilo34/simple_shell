#include "main.h"

/**
 * bg_strdup - Duplicate a string.
 * @str: The string to be duplicated.
 * Return: A duplicated string or NULL on failure.
 */
char *gb_strdup(const char *input)
{
	char *new_str;
	size_t length, i;

    if (input == NULL)
    {
        return NULL;
    }

    length = gb_strlen(input) + 1;
    new_str = (char *)malloc(length * sizeof(char));

    if (new_str == NULL)
        return NULL;

    i = 0;
    while (input[i] != '\0')
    {
        new_str[i] = input[i];
        i++;
    }
    new_str[i] = '\0';

    return new_str;
}

