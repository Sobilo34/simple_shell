#include "main.h"

#define INITIAL_BUFFER_SIZE 1024


/**
 * our_getline - This is our getline function getline function
 * @line: line buffer
 * @len: length of buffer
 * @stream: stream to read from
 * Return: number of characters read or -1 if fail
 */
ssize_t gb_getline(char **line_ptr, size_t *len_siz, FILE *stream)
{
	ssize_t read_char;
	char *the_getline;
	char *line = *line_ptr;
	size_t size = *len_siz;

	if (line == NULL || size == 0)
	{
		size = INITIAL_BUFFER_SIZE;
		line = malloc(size);
		if (line == NULL)
		{
			perror("malloc");
			return (-1);
		}
	}

	the_getline = fgets(line, (int)size, stream);
	if (the_getline != NULL)
	{
		read_char = strlen(line);

		if (read_char > 0 && line[read_char - 1] == '\n')
		 {
			 line[read_char - 1] = '\0';
			 read_char--;
		 }

		 *line_ptr = line;
		 *len_siz = size;
		 return (read_char);
	}
	return (-1);
}
