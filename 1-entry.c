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
	int idx;
	(void)argc;

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
		{
			write(1, "#cisfun$ ", 10);
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

		if (args[0] == NULL)/**For empty command, go back to the loop**/
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

		if (access(args[0], X_OK) == 0)
		{

			paid = fork();
			if (paid == -1)
			{
				perror("there was an error\n");
				free(buffer);
				exit(EXIT_FAILURE);
			}

			if (paid == 0)
			{
				exec_cmd(args, env);
				perror("Exec failure");
				exit(EXIT_FAILURE);
			}

			else
				wait(NULL);
		}
		else
			perror("./hsh");
	}
	return (0);
}

