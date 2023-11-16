#include "main.h"

/**
 * print_env - Print the environment variables.
 * @env: The array of environment variables.
 */

void print_env(char **env)
{
	int status;
	pid_t paid;

	paid = fork();
	if (paid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (paid == 0)
	{
		char *args[] = {"/usr/bin/env", NULL};

		env = environ;
		execve("/usr/bin/env", args, env);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
		wait(&status);
}
