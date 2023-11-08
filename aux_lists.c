#include "main.h"

/**
 * list_len - This function determines length of linked list
 * @bg: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *bg)
{
	size_t a = 0;

	while (bg)
	{
		bg = bg->next;
		a++;
	}
	return (a);
}

/**
 * list_to_strings - This function returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *n = head;
	size_t o = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !o)
		return (NULL);
	strs = malloc(sizeof(char *) * (o + 1));
	if (!strs)
		return (NULL);
	for (o = 0; n; n = n->next, o++)
	{
		str = malloc(_strlen(n->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, n->str);
		strs[o] = str;
	}
	strs[o] = NULL;
	return (strs);
}


/**
 * print_list - This function prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: Returns the size of list
 */
size_t print_list(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		a++;
	}
	return (a);
}

/**
 * node_starts_with - This function returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: Returns the match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *o = NULL;

	while (node)
	{
		o = starts_with(node->str, prefix);
		if (o && ((c == -1) || (*o == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t o = 0;

	while (head)
	{
		if (head == node)
			return (o);
		head = head->next;
		o++;
	}
	return (-1);
}

