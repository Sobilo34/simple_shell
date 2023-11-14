#include "main.h"

/**
 * our_getline - This is our getline function getline function
 * @line: line buffer
 * @len: length of buffer
 * @stream: stream to read from
 * Return: number of characters read or -1 if fail
 */
ssize_t gb_getline(char **line_ptr, size_t *len_siz, FILE *stream)
{
	ssize_t read_char, p_len = 0;
	char *the_getline;
	char *line = *line_ptr;
	size_t size = *len_siz;

	if (line == NULL || size == 0)
	{
		size = 1024;
		line = malloc(size);
		if (line == NULL)
			return (-1);
	}

	while (1)
	{
		the_getline = fgets(line + p_len, (int)size, stream);
		if (the_getline == NULL)
		{
			if (p_len == 0)
			{
				free(line);
				*line_ptr = NULL;
				*len_siz = 0;
				return (-1);
			}

			else
			{
				*line_ptr = line;
				*len_siz = size;
				return (p_len);
			}
		}
		read_char = gb_strlen(line + p_len);

		if (read_char > 0 && line[read_char - 1] == '\n')
		{
			line[p_len + read_char - 1] = '\0';
			*line_ptr = line;
			*len_siz = size;

			return (p_len + read_char);
		}
		p_len += read_char;

		if (size - p_len <= 1)
		{
			size *= 2;
			line = realloc(line, size);
			if (line == NULL)
			{
				return (-1);
			}
		}
	}
}
