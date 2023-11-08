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
        pid_t paid;
        ssize_t message;
        size_t len;
        char *buffer, *token = NULL, *exit_code;
        char *args[1024], *delim = " \t\r\a", *prompt = "#cisfun:";
	char curr_dir[PATH_MAX];
        int idx, stat;
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
			write(1, " ", 2);
			fflush(stdout);
                }
                message = gb_getline(&buffer, &len, stdin);
                if (message == -1)
                {
                        write(0, "\n", 2);
                        free(buffer);
			exit(0);	
                }

                if (buffer[message -1] == '\n')
                {
                        buffer[message -1] = '\0';
                }

                idx = 0;
                token = gb_strtok(buffer, delim);

                while (token != NULL)
                {
                        args[idx] = token;
                        token = gb_strtok(NULL, delim);
                        idx++;
                }
                args[idx] = NULL;

                if (args[0] == NULL)/**For empty command, go back to the loop**/
                        continue;

                if (gb_strcmp(args[0], "exit") == 0)
                {
			exit_code = args[1];
                        if (exit_code != NULL)
			{
				stat = atoi(args[1]);
				exit(stat);
			}

			else
			{
				exit(0);
			}
                }

                if (gb_strcmp(args[0], "env") == 0 ||
                                strcmp(args[0], "/bin/env") == 0)
                {
                        print_env(env);
                        continue;
                }

		if (gb_strcmp(args[0], "cd") == 0)
		{
			if (change_curr_dir(args) == -1)
			{
				perror("cant change dir\n");
			}
			continue;
		}

                if (check_cmd(&args[0]) == 1)
                {

                        paid = fork();
                        if (paid == -1)
                        {
                                error_prt(args[0], "./fork");
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
                        error_prt(args[0], "./hsh");
        }
        return (0);
}
