#include "main.h"
#include <stdarg.h>
#include <stdio.h>

#define BUFFER_SIZE 1024

/**
 * gb_print - This is to print a formatted string to stdout.
 * @format: The format string, similar to printf.
 * @...: Additional arguments for placeholders in the format string.
 */
void gb_print(const char *format, ...)
{
	int length;
	va_list args;
	char buffer[BUFFER_SIZE];

	va_start(args, format);
	length = vsnprintf(buffer, BUFFER_SIZE, format, args);
	va_end(args);

	if (length < 0 || length >= BUFFER_SIZE)
	{
		return;
	}
	write(STDOUT_FILENO, buffer, length);
}

/**
 * gb_setenv - Set or modify an environment variable
 * @variable: The name of the environment variable
 * @value: The value to set for the environment variable
 * @env: The environment variables
 * Return: 0 on success, -1 on failure
 */

int gb_setenv(const char *variable, const char *value, char ***env)
{
	char *env_variable;
	int i;
	char buffer[1024];

	if (variable == NULL || value == NULL || env == NULL || *env == NULL)
	{
	gb_print("setenv: Invalid arguments\n");
	return (-1);
	}
	gb_strcpy(buffer, variable);
	env_variable = gb_strcat(buffer, value);
	if (env_variable == NULL)
	{
		gb_print("setenv: Memory allocation failure\n");
		return (-1);
	}
	for (i = 0; (*env)[i] != NULL; i++)
	{
		if (gb_strstartswith((*env)[i], variable))
		{
			free((*env)[i]);
			(*env)[i] = env_variable;
			return (0);
		}
	}

	*env = realloc(*env, (i + 2) * sizeof(char *));
	if (*env == NULL)
	{
		gb_print("setenv: Memory allocation failure\n");
		free(env_variable);
		return (-1);
	}
		(*env)[i] = env_variable;
		(*env)[i + 1] = NULL;
		return (0);
}




/**
 * gb_unsetenv - Unset an environment variable
 * @variable: The name of the environment variable to unset
 * @env: The environment variables
 * Return: 0 on success, -1 on failure
 */
int gb_unsetenv(const char *variable, char ***env)
{
	int i, j;

	if (variable == NULL || env == NULL || *env == NULL)
	{
		gb_print("unsetenv: Invalid arguments\n");
		return (-1);
	}

	for (i = 0; (*env)[i] != NULL; i++)
	{
		if (gb_strstartswith((*env)[i], variable))
		{
			free((*env)[i]);

			for (j = i; (*env)[j + 1] != NULL; j++)
			(*env)[j] = (*env)[j + 1];
			(*env)[j] = NULL;
				return (0);
		}
	}
	gb_print("unsetenv: Variable not found\n");
	return (-1);
}

/**
 * gb_strstartswith - Check if a string starts with a given prefix
 * @str: The string to check
 * @prefix: The prefix to check for
 * Return: 1 if str starts with the prefix, 0 otherwise
 */
int gb_strstartswith(const char *str, const char *prefix)
{
	while (*prefix != '\0')
	{
	if (*prefix != *str)
	return (0);
		prefix++;
		str++;
	}
	return (1);
}
