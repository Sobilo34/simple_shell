#include "main.h"

int num_aliases = 0;

/**
 * print_alias - This is the function that Prints alias
 * @name: The name of the alias
 */
void print_alias(char *name)
{
	int i;

    for (i = 0; i < num_aliases; i++)
    {
        if (gb_strcmp(aliases[i].name, name) == 0)
	{
            printf("%s='%s'\n", aliases[i].name, aliases[i].value);
            return;
        }
    }
    printf("Alias '%s' not found\n", name);
}


/**
 * handle_alias_command - Handle the alias command
 * @args: Array of command arguments
 */
void handle_alias_command(char **args)
{
	int i;
	char *name, *value;

    if (args[1] == NULL)
    {
        /**Print all aliases**/
        for (i = 0; i < num_aliases; i++)
	{
            printf("%s='%s'\n", aliases[i].name, aliases[i].value);
        }
    }
    
    else
    {
        /**Define or print specific aliases**/
        for (i = 1; args[i] != NULL; i++)
	{
            if (args[i + 1] != NULL && args[i + 1][0] == '=')
	    {
                /**Define an alias**/
                name = gb_strtok(args[i], "=");
                value = gb_strtok(NULL, "=");
                define_alias(name, value);
            }
	    else
	    {
                /**Print an alias**/
                print_alias(args[i]);
            }
        }
    }
}




/**
 * define_alias - Define an alias
 * @name: Alias name
 * @value: Alias value
 */
void define_alias(char *name, char *value)
{
	int i;

    if (num_aliases < MAX_ALIASES)
    {
        /**Check if the alias already exists, and if it does, update it**/
        for (i = 0; i < num_aliases; i++)
	{
            if (gb_strcmp(aliases[i].name, name) == 0)
	    {
                aliases[i].value = value;
                return;
            }
        }
        aliases[num_aliases].name = name;
        aliases[num_aliases].value = value;
        num_aliases++;
    }
    
    else
    {
        printf("Too many aliases defined\n");
    }
}
