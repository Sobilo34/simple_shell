#include "main.h"

/**
 * exec_cmd - This function will execute the command
 * @args: The command and its arguments
 * @env: The environment variables
 * Return: Nothing
 */
void exec_cmd(char **args, char **env)
{
    char *full_path = getenv("PATH"), *path, *token;
    char our_path[1024];

    if (args[0] == NULL)
    {
        perror("Command not provided");
        exit(EXIT_FAILURE);
    }

    if (args[0][0] == '/')
    {
        if (access(args[0], X_OK) == 0)
        {
            execve(args[0], args, env);
            perror("Unable to execute");
            exit(EXIT_FAILURE);
        }
        else
        {
            perror("Command not found");
            exit(EXIT_FAILURE);
        }
    }

    if (full_path == NULL)
    {
        perror("Unable to locate PATH environment variable");
        exit(EXIT_FAILURE);
    }

    path = gb_strdup(full_path);
    if (path == NULL)
    {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    token = gb_strtok(path, ":");
    while (token != NULL)
    {
        gb_strcpy(our_path, token);
        gb_strcat(our_path, "/");
        gb_strcat(our_path, args[0]);

        if (access(our_path, X_OK) == 0)
        {
            execve(our_path, args, env);
        }

        token = gb_strtok(NULL, ":");
    }

    perror("Command not found");
    free(path);
    exit(EXIT_FAILURE);
}

