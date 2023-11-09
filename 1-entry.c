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
        char *args[1024], *delim = " \t\r\a", *prompt = "#cisfun:";
	char *commands[1024];
	int num_commands, i;
    char curr_dir[PATH_MAX];
    int idx, success = 1;
    (void)argc;


    while (1) {
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

        /**Split the input into commands**/
        num_commands = split_commands(buffer, commands);

        for (i = 0; i < num_commands; i++)
	{
            idx = 0;
            token = gb_strtok(commands[i], delim);

            while (token != NULL)
	    {
                args[idx] = token;
                token = gb_strtok(NULL, delim);
                idx++;
            }

            success = execute_command(args, env, success);
        }
    }
    return (0);
}



/**
 * split_commands - Split the input string into separate commands
 * @input: The input string
 * @commands: Array to store the split commands
 * Return: Number of split commands
 */
int split_commands(char *input, char *commands[])
{
    int num_commands = 0;
    char *token = gb_strtok(input, ";"); /**Split by semicolon to separate commands**/

    while (token != NULL)
    {
        commands[num_commands++] = token;
        token = gb_strtok(NULL, ";");
    }

    return num_commands;
}



/**
 * execute_command - Execute a single command or handle "&&" and "||" operators
 * @args: Array of command arguments
 * @env: Array of environment variables
 * @success: Current command success status
 * Return: 1 if the command succeeded, 0 if it failed
 */
int execute_command(char **args, char **env, int success)
{
    /**Check for logical operators in the arguments**/
    char *logical_operator = NULL, *exit_code;
    int i, a, exit_status, status,command_result;

    for (i = 0; args[i] != NULL; i++)
    {
        if (gb_strcmp(args[i], "&&") == 0)
	{
            logical_operator = "&&";
            args[i] = NULL; /**Set the operator as a terminator**/
            break;
        }
	else if (gb_strcmp(args[i], "||") == 0)
	{
            logical_operator = "||";
            args[i] = NULL; /**Set the operator as a terminator**/
            break;
        }
    }

    if (args[0] == NULL) {
        /**For empty command, continue to the next iteration**/
        return success;
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
        return success;
    }

    if (gb_strcmp(args[0], "cd") == 0)
    {
        if (change_curr_dir(args) == -1)
	{
            perror("can't change dir");
            return 0; /**Command failed**/
        }
        return 1; /** Command succeededi**/
    }

    for (a = 0; a < MAX_ALIASES; a++)
    {
            aliases[a].name = NULL;
            aliases[a].value = NULL;
    }

    if (gb_strcmp(args[0], "alias") == 0)
    {
	    handle_alias_command(args);
	    return (success);
    }


    if (check_cmd(args) == 1)
    {
        pid_t child_pid = fork();
        if (child_pid == -1)
	{
            error_prt(args[0], "fork");
            return 0; /**Command failed**/
        }

        if (child_pid == 0)
	{
            exec_cmd(args, env);
            perror("Exec failure");
            exit(EXIT_FAILURE);
        }
	
	else
	{
            wait(&status);
            command_result = WIFEXITED(status) ? WEXITSTATUS(status) : 1;
            
            if (logical_operator == NULL)
	    {
                /**No logical operator, return the command result**/
                return command_result;
            }
	    
	    else if (gb_strcmp(logical_operator, "&&") == 0)
	    {
                /**Handle logical AND (&&)**/
                return (command_result == 0) ? success : 0;
            }
	    
	    else if (gb_strcmp(logical_operator, "||") == 0)
	    {
                /**Handle logical OR (||)**/
                return (command_result == 0) ? 0 : success;
            }
        }
    }

    else
	    error_prt(args[0], "./hsh");

    return 0;
}
