#include "main.h"

/**
 * gb_strcpy - This is a function that is used to copy string
 * @scr: The source where the string is copied
 * @dest: The destination where the string is being copied to
 * Return: The pointer/address od the destination
 */

char *gb_strcpy(char *dest, const char *scr)
{
	int scr_len = 0;
	int i = 0;

	scr_len = 0;
	while (scr[scr_len] != '\0')
		scr_len++;
	i = 0;
	while (i < scr_len)
	{
		dest[i] = scr[i];
		i++;
	}

	dest[i] = '\0';

	return (dest);
}
