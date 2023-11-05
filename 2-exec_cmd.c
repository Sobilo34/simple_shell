#include "main.h"

/**
 * exec_success - This is the function that will execute the command
 * Return: Nothing
 */

char *exec_cmd(char **args, char **env)
{
	char *full_path = getenv("PATH");
	char *token, *our_path;

	if (args[0] == NULL)
	{
		write(2, "Empty command\n", 14);
	}

	if (execve(args[0], args, env) == -1)
	{
		perror("Execution error");
	}
	else if (args[0][0] == '/')
	{
		if (access(args[0], X_OK) == 0)
		{
			execve(args[0], args, env);
			write(2, "Unable to execute\n", 18);
		}
		else
		{
			write(2, "Command not found\n", 18);
		}
	}
	else if (full_path == NULL)
	{
		write(2, "Unable to locate PATH\n", 23);
	}
	else
	{
	token = strtok(full_path, ":");
	while (token != NULL)
	{
		our_path = malloc(strlen(token) + strlen(args[0]) + 2);
		if (our_path == NULL)
		{
			 write(2, "Unable to allocate memory\n", 27);
		}
		else
		{
			strcpy(our_path, token);
			strcat(our_path, "/");
			strcat(our_path, args[0]);

		if (access(our_path, X_OK) == 0)
		{
			execve(our_path, args, env);
			write(2, "Unable to execute\n", 18);
		}

		free(our_path);
		}
		token = strtok(NULL, ":");
	}
	write(2, "Command not found in PATH\n", 27);
	}
	return(args[0]);
}


