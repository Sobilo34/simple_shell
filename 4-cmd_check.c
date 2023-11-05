#include "main.h"
/**
 * check_cmd - check if the command exist in the
 * path, if it does not creat a path and append it to the directory
 * @str: pointer to the command.
 *
 * Return: return a status value of 1 on success and 0 on failure.
 */
int check_cmd(char **input)
{
	char *path, *token, *bufa;
	static char path_bufa[1024];

	path = getenv("PATH");
	if (path == NULL)
	{
		return (0);
	}

	if (path == NULL || *input == NULL || input == NULL)
		return (0);

	if (access(*input, X_OK) == 0 && (*input)[0] == '/')
		return (1);


	strcpy(path_bufa, path);
	token = strtok(path_bufa, ":");
	while (token != NULL)
	{
		bufa = malloc(strlen(token) + strlen(*input) + 2);
		if (bufa == NULL)
		{
			perror(*input);
			return (0);
		}

		strcpy(bufa, token);
		strcat(bufa, "/");
		strcat(bufa, *input);

		if (access(bufa, X_OK) == 0)
		{
			*input = bufa;
			return (1);
		}
		free(bufa);
		token = strtok(NULL, ":");
	}
	perror(*input);
	return (0);
}
