#include "main.h"

void prt_alias(char *name);

/**
 * prt_alias - This is the function that Prints alias
 * @name: The name of the alias to be printed
 * Return: Nothing
 */
void prt_alias(char *name)
{
	int i, num_aliases = 0;

	for (i = 0; i < num_aliases; i++)
	{
		if (gb_strcmp(aliases[i].name, name) == 0)
		{
			write(STDOUT_FILENO, aliases[i].name,
					gb_strlen(aliases[i].name));
			write(STDOUT_FILENO, "='", 2);
			write(STDOUT_FILENO, aliases[i].value,
					gb_strlen(aliases[i].value));
			write(STDOUT_FILENO, "'\n", 2);

			return;
		}
	}
	write(STDOUT_FILENO, "Alias '", 7);
	write(STDOUT_FILENO, name, gb_strlen(name));
	write(STDOUT_FILENO, "' not found\n", 12);

}


/**
 * handle_alias - THis is the function that handles the alias command
 * @args: command arguments arrays
 * Return: Nothing
 */
void handle_alias(char **args)
{
	int i;
	int num_aliases = 0;
	char *name, *value;

	if (args[1] == NULL)
	{
		for (i = 0; i < num_aliases; i++)
		{
			write(STDOUT_FILENO, aliases[i].name,
				gb_strlen(aliases[i].name));
			write(STDOUT_FILENO, "='", 2);
			write(STDOUT_FILENO, aliases[i].value,
				gb_strlen(aliases[i].value));
			write(STDOUT_FILENO, "'\n", 2);
		}
	}

	else
	{
		/**To define or print specific aliases**/
		for (i = 1; args[i] != NULL; i++)
		{
			if (args[i + 1] != NULL && args[i + 1][0] == '=')
			{
				/**To define an alias**/
				name = gb_strtok(args[i], "=");
				value = gb_strtok(NULL, "=");
				define_alias(name, value);
			}
			else
			{
				/**To print an alias**/
				prt_alias(args[i]);
			}
		}
	}
}




/**
 * define_alias - THis is a function that defines an alias
 * @name: The name of the alias
 * @value: The alias value
 * Return: Nothing
 */
void define_alias(char *name, char *value)
{
	int i;
	int num_aliases = 0;

	if (num_aliases < ALIAS_MAX)
	{
		/**Update alias if there is**/
		for (i = 0; i < num_aliases; i++)
		{
			if (gb_strcmp(aliases[i].name, name) == 0)
			{
				free(aliases[1].value);
				aliases[i].value = gb_strdup(value);
				return;
			}
		}
		aliases[num_aliases].name = gb_strdup(name);
		aliases[num_aliases].value = gb_strdup(value);
		num_aliases++;
	}
	else
	{
		write(STDOUT_FILENO, "Too many aliases defined\n", 30);
	}
}
