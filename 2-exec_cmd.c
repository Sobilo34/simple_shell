#include "main.h"

/**
 * exec_success - This is the function that will execute the command
 * Return: Nothing
 */

char *exec_cmd(char **args, char **env)
{
	char *full_path = getenv("PATH"), *token, *our_path;

	if (args[0] == NULL)
	{
		exit(EXIT_FAILURE);
	}

	if (args[0][0] == '/')
	{
		if (access(args[0], X_OK) == 0)
		{
			execve(args[0], args, env);
			perror("Unable to execute\n");
			exit(EXIT_FAILURE);
		}
		else
		{
			perror("Command not found\n");
			exit(EXIT_FAILURE);
		}
	}

	if (full_path == NULL)
	{
		perror("Unable to locate env\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(full_path, ":");
	while (token != NULL)
	{
		our_path = malloc(strlen(token) + strlen(args[0]) + 2);
		if (our_path == NULL)
		{
			perror("Unable to allocate memory");
			exit(EXIT_FAILURE);
		}
		sprintf(our_path, "%s/%s", token, args[0]);

		if (access(our_path, X_OK) == 0)
		{
			execve(our_path, args, env);
			perror("Unable to execute");
			free(our_path);
			exit(EXIT_FAILURE);
		}

		free(our_path);
		token = strtok(NULL, ":");
	}
	return(args[0]);
}

