#include "shell.h"


/**
 * handle_setenv - This function handles the "setenv" built-in command.
 * @dash: The Pointer to the data structure holding shell data.
 * @args: The Array of command arguments.
 */
void handle_setenv(data_sh *dash, char **args)
{
	if (args[1] != NULL && args[2] != NULL)
	{
	if (setenv(args[1], args[2], 1) == -1)
	{
	perror("setenv");
	dash->status = EXIT_FAILURE;
	}
	}
	else
	{
	dash->status = EXIT_FAILURE;
	fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
	}
}

/**
 * handle_unsetenv - Handle the "unsetenv" built-in command.
 * @dash: Pointer to the data structure holding shell data.
 * @args: Array of command arguments.
 */
void handle_unsetenv(data_sh *dash, char **args)
{
	if (args[1] != NULL)
	{
	if (unsetenv(args[1]) == -1)
	{
	perror("unsetenv");
	dash->status = EXIT_FAILURE;
}
	}
	else
	{
	dash->status = EXIT_FAILURE;
	fprintf(stderr, "Usage: unsetenv VARIABLE\n");
	}
}

