#include "main.h"

/**
 * gb_strcmp - This is the functio that will be used to compare two strings
 * @str1: The first sring to compare
 * @str2: The second string to be compared to
 * Return: 0 if strings are equal, value greater than zero
 * if str1 > str2 and value less than zero if str2 > str1
 */

int gb_strcmp(const char *str1, const char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)/**loop for comparison**/
	{
		str1++;
		str2++;
	}

	if (*str1 == *str2)/**Compare if str1 and str2 are equal**/
		return (0);/**return zero if yes**/
	else if (*str1 < *str2)/**compare if str1 is less than str2**/
		return (-1);/**return a negative value if yes**/
	else/**unless the two condition s which means str2 is less than str1**/
		return (1);/**return a positive value**/
}
