#include "main.h"

/**
 * main - This is the entry point of all functions
 * @argc: The is the arguments
 * @env: This represents the environment variable
 * Return: 0 on Success, and -1 on failure
 */

int main(int argc, char **env)
{
	pid_t paid;
	ssize_t message;
	size_t len;
	char *buffer, *token = NULL;
	char *args[1024], *delim = " \t\r\a";
	int idx, status = 0;
	(void)argc;

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
		{
			write(1, "$ ", 2);
			fflush(stdout);
		}
		message = getline(&buffer, &len, stdin);
		if (message == -1)
		{
			write(0, "\n", 2);
			free(buffer);
			exit(EXIT_FAILURE);
		}

		if (buffer[message -1] == '\n')
		{
			buffer[message -1] = '\0';
		}

		idx = 0;
		token = strtok(buffer, delim);
		
		while (token != NULL)
		{
			args[idx] = token;
			token = strtok(NULL, delim);
			idx++;
		}
		args[idx] = NULL;

		if (args[0] == NULL)
			continue;
		if (strcmp(buffer, "exit") == 0)
		{
			exit(0);
		}

		if (strcmp(args[0], "env") == 0 ||
				strcmp(args[0], "/bin/env") == 0)
		{
			print_env(env);
			continue;
		}

		paid = fork();
		if (paid == -1)
		{
			perror("there was an error\n");
			exit(EXIT_FAILURE);
			free(buffer);
		}

		if (paid == 0)
		{
			exec_cmd(args, env);
		}

		else
			wait(&status);
	}
	return (0);
}

