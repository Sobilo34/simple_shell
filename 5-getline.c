#include "main.h"
/**
 * gb_getline - Read a line of input from a file stream
 * @lineptr: A pointer to the buffer where the line is stored
 * @n: A pointer to the size of the buffer
 * @stream: The file stream to read from
 *
 * Return: The number of characters read on success, or -1 on failure
 */
int gb_getline(char **lineptr, size_t *n, FILE *stream)
{
	size_t i = 0, size = *n;
	int c;
	char *line = *lineptr, *new_ptr;

	if (*lineptr == NULL || *n == 0)
	*n = 128;
	*lineptr = (char *)malloc(*n);
	if (*lineptr == NULL)
	return (-1);
	line = *lineptr;
	while (1)
	{
		c = fgetc(stream);
	if (c == EOF)
	{
	line[i] = '\0';
	*n = size;
	return ((i > 0) ? (int)i : -1);
	}
	else if (c == '\n')
	{
		line[i] = '\0';
	return ((int)i);
	}
	line[i] = (char)c;
	i++;
	if (i >= size - 1)
	{
	size += 128;
	new_ptr = (char *)realloc(line, size);
	if (new_ptr == NULL)
	{
		free(line);
		*lineptr = NULL;
		return (-1);
	}
	line = new_ptr;
	*lineptr = line;
	}
	}
}

