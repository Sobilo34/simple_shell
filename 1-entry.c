#include "main.h"

#define PATH_MAX 4096
/**
 * main - This is the entry point of all functions
 * @argc: The is the arguments
 * @env: This represents the environment variable
 * Return: 0 on Success, and -1 on failure
 */

int main(int argc, char **env)
{
	/* pid_t paid; **/
	ssize_t message;
	size_t len;
	char *buffer, **env_ptr, *token = NULL;
	char *args[1024], *delim = " \n\t\r\a";
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
		if (message <= 0)
		{
			free(buffer);
			if (message == -1)
			{
				perror("getline");
			}
			exit(EXIT_SUCCESS);
		}

		token = strtok(buffer, delim);
		if (token == NULL)
		{
			continue;
		}
		if (strcmp(token, "exit") == 0)
		{
			free(buffer);
			break;
		}
		else if (strcmp(token, "env") == 0)
		{
			env_ptr = env;
			while (*env_ptr)
			{
				printf("%s\n", *env_ptr);
				env_ptr++;
			}
		}
		else
		{
			idx = 0;
		while (token != NULL)
		{
			args[idx] = token;
			token = strtok(NULL, delim);
			idx++;
		}
		args[idx] = NULL;
		
		if (check_cmd(&args[0]))
		{
		exec_cmd(args, env);
		}
	}
	}
	free(buffer);
	perror("./hsh");
	return (0);
}



