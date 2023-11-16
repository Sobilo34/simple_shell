#include "main.h"

int check_cmd(char **input);

/**
 * check_cmd - check if the command exist in the
 * path, if it does not creat a path and append it to the directory
 * @input: pointer to the command.
 *
 * Return: return a status value of 1 on success and 0 on failure.
 */
int check_cmd(char **input)
{
	char *path, *token, *bufa;
	static char path_bufa[1024];
	int i;
	int num_aliases = 0;


	for (i = 0; i < num_aliases; i++)
	{
		if (gb_strcmp(input[0], aliases[i].name) == 0)
		{
			input[0] = aliases[i].value; /**Replace the alias with its value**/
			return (1);
		}
	}

	path = getenv("PATH");
	if (path == NULL || *input == NULL || input == NULL)
		return (0);

	if (access(*input, X_OK) == 0 && (*input)[0] == '/')
	{
		return (1);
	}


	gb_strcpy(path_bufa, path);
	token = gb_strtok(path_bufa, ":");
	while (token != NULL)
	{
		bufa = malloc(gb_strlen(token) + gb_strlen(*input) + 2);
		if (bufa == NULL)
		{
			perror("gb_strtok");
			return (0);
		}

		gb_strcpy(bufa, token);
		gb_strcat(bufa, "/");
		gb_strcat(bufa, *input);

		if (access(bufa, X_OK) == 0)
		{
			return (1);
		}
		free(bufa);
		token = gb_strtok(NULL, ":");
	}
	return (0);
}
