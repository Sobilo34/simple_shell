#include "main.h"
char *gb_strtok(char *input, const char *delimt);
/**
 * gb_strtok - THis is our custom strtok function used to tokenize strings
 * @input: THe string input by  user to be tokenized
 * @delimt: The delimeter of the strings
 * Return: The token tokenised from the string
 */

char *gb_strtok(char *input, const char *delimt)
{
	static char *ptr;/**Use a static char to save the tokens tokenized**/
	char *token = NULL;
	size_t a, b;

	if (input != NULL)/** To test if there if there is an input string**/
	{
		ptr = input;/** Input will be save in the pointer**/
	}
	if (ptr == NULL || *ptr == '\0')
	{
		return (NULL);
	}

	token = ptr;/** The string to be tokenised is the input strored in the ptr**/
	a = 0;
	while (delimt[a])/** Check if delimeter is found in the ptr**/
	{
		if (*ptr == delimt[a])
		{
			*ptr = '\0';
			ptr++;
			return (token);
		}
		a++;
	}

	while (*ptr)/** Checks the ptr and find the character
		      *that match the delimeter **/
	{
		b = 0;
		while (delimt[b])
		{
			if (*ptr == delimt[b])
			{
				*ptr = '\0';
				ptr++;
				return (token);
			}
			b++;
		}
		ptr++;
	}

	return (token);
}
