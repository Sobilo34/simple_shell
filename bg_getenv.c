#include "main.h"

/**
 * get_env - This function returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always returns 0.
 */
char **get_env(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - This function removes an environment variable.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 *
 * Return: returns 1 on delete, 0 otherwise
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *n = info->env;
	size_t i = 0;
	char *a;

	if (!n || !var)
		return (0);

	while (n)
	{
		a = starts_with(n->str, var);
		if (a && *a == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			n = info->env;
			continue;
		}
		n = n->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenv - This function initializes a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always returns 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *f = NULL;
	list_t *node;
	char *a;

	if (!var || !value)
		return (0);

	f = malloc(_strlen(var) + strlen(value) + 2);
	if (!f)
		return (1);
	strcpy(f, var);
	strcat(f, "=");
	strcat(f, value);
	node = info->env;
	while (node)
	{
		a = starts_with(node->str, var);
		if (a && *a == '=')
		{
			free(node->str);
			node->str = f;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), f, 0);
	free(f);
	info->env_changed = 1;
	return (0);
}

