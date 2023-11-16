#include "main.h"

int change_curr_dir(char **args);
/**
 * change_curr_dir - This is the fucntion that changes the
 * current working directory to another
 * @args: The arument for the command
 * Return: 0 on success and -1 if failed
 */

int change_curr_dir(char **args)
{
	char *path, prev_dir[PATH_MAX], curr_dir[PATH_MAX];

	if (args[1] == NULL || (args[1][0] == '~' && (args[1][1] == '\0'
					|| args[1][1] == '/')))
	{
		path = getenv("HOME");
	}
	else if (args[1][0] == '-' && args[1][1] == '\0')
	{
		path = getenv("OLDPWD");
	}
	else
		path = args[1];

	if (access(path, X_OK) != 0)
	{
		dprintf(STDERR_FILENO,
			"./hsh: 1: cd: can't cd to %s\n", path);
		return (-1);
	}

	if (chdir(path) != 0)
	{
		return (-1);
	}

	if (getcwd(prev_dir, sizeof(curr_dir)) == NULL)
	{
		return (-1);
	}

	if (setenv("OLDPWD", prev_dir, 1) != 0)
		return (-1);

	if (getcwd(curr_dir, sizeof(curr_dir)) == NULL)
		return (-1);

	if (setenv("PWD", curr_dir, 1) != 0)
		return (-1);

	return (0);
}
