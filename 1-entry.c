#include "main.h"

void bilalandgrace(void);

/**
 * main - This is the entry point of all functions
 * @argc: The is the arguments
 * @env: This represents the environment variable
 * Return: 0 on Success, and -1 on failure
 */

int main(int argc, char **env)
{
        ssize_t message;
        size_t len;
        char *buffer, *token = NULL;
        char *args[1024], *delim = " \t\r\a", *prompt = "#cisfun:", *comm_start;
	char *commands[1024];
	int value, i;
	char curr_dir[PATH_MAX];
	int idx, success = 1;
	(void)argc;

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
		{
			if (getcwd(curr_dir, PATH_MAX) == NULL)
			{
				perror("getcwd");
				exit(EXIT_FAILURE);
			}
			write(STDOUT_FILENO, prompt, gb_strlen(prompt));
			write(STDOUT_FILENO, curr_dir, gb_strlen(curr_dir));
			write(STDOUT_FILENO, "$ ", 2);
			fflush(stdout);
		}

		message = gb_getline(&buffer, &len, stdin);
		if (message == -1)
		{
			write(0, "\n", 1);
			free(buffer);
			exit(0);
		}

		if (buffer[message - 1] == '\n')
		{
			buffer[message - 1] = '\0';
		}

		comm_start = strchr(buffer, '#');
		if (comm_start != NULL)
		{
			*comm_start = '\0';
		}

		/*To split the input into commands**/
		value = split_cmds(buffer, commands);
		for (i = 0; i < value; i++)
		{
			idx = 0;
			token = gb_strtok(commands[i], delim);

			while (token != NULL)
			{
				args[idx] = token;
				token = gb_strtok(NULL, delim);
				idx++;
			}
			args[idx] = NULL;

			success = exec_with_operator(args, env, success);
		}

	}
	return (0);
}



/**
 * split_cmds - This is the funtion that spilts string to different commands
 * @input: The user's input
 * @commands: The array to store the splitted commands
 * Return: Value of the commads splitted
 */
int split_cmds(char *input, char *cmd[])
{
	int value = 0;/**Number of commands**/
	char *token;
       
	token = gb_strtok(input, ";"); /**split commands with ";"**/
	while (token != NULL)
	{
		cmd[value] = token;
		value++;
		token = gb_strtok(NULL, ";");
	}

	return (value);
}



/**
 * exec_with_operator - This is the function that execute command and handle "&&" and "||" operators
 * @args: command arguments array
 * @env: Array of environment variables
 * @success: Status of success of commands
 * Return: 1 if the command succeeded and 0 if it failed
 */
int exec_with_operator(char **args, char **env, int success)
{
	pid_t pid, paid;
	char *operator = NULL, *exit_code;
	int i, a, exit_status, status, result;

	for (i = 0; args[i] != NULL; i++)
	{
		if (gb_strcmp(args[i], "&&") == 0)
		{
			operator = "&&";
			args[i] = NULL;
			break;
		}
		
		else if (gb_strcmp(args[i], "||") == 0)
		{
			operator = "||";
			args[i] = NULL;
			break;
		}
	}

	if (args[0] == NULL)
	{
		return (success);
	}

	if (gb_strcmp(args[0], "exit") == 0)
	{
		exit_code = args[1];
		exit_status = (exit_code != NULL) ? atoi(exit_code) : 0;
		exit(exit_status);
	}

	if (gb_strcmp(args[0], "env") == 0 || gb_strcmp(args[0], "/bin/env") == 0)
	{
		print_env(env);
		return (success);
	}

	if (gb_strcmp(args[0], "cd") == 0)
	{
		if (change_curr_dir(args) == -1)
		{
			perror("can't change dir");
			return 0;
		}
		else
			return 1;
	}

	for (a = 0; a < ALIAS_MAX; a++)
	{
		aliases[a].name = NULL;
		aliases[a].value = NULL;
	}

	if (gb_strcmp(args[0], "alias") == 0)
	{
		handle_alias(args);
		return (success);
	}


	pid = getpid();
	if (check_cmd(args) == 1)
	{
		args[0] = replace_implement(args[0], status, pid);
		paid = fork();
		if (paid == -1)
		{
			error_prt(args[0], "fork");
			exit(EXIT_FAILURE);
		}

		if (paid == 0)
		{
			exec_cmd(args, env);
			perror("Exec failure");
			exit(EXIT_FAILURE);
		}
		
		else
		{
			wait(&status);
			result = WIFEXITED(status) ? WEXITSTATUS(status) : 1;
			if (operator == NULL)/**When there is no logical operator**/
			{
				return (result);
			}
			
			else if (gb_strcmp(operator, "&&") == 0)
			{
				return (result == 0) ? success : 0;
			}
	    
			else if (gb_strcmp(operator, "||") == 0)
			{
				return ((result == 0) ? 0 : success);
			}
		}
	}

	else
		error_prt(args[0], "./hsh");

	return (0);
}
