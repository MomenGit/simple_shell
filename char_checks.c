#include "main.h"

/**
 * is_delim - checks if character is a delimeter
 * @c: character  to check
 * @delim: delimeter string
 * Return: if true return 1, if false return 0
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - checks for alphabetic character
 * @c: The character to input
 * Return: if c is alphabetic return 1, otherwise return 0
 */

int _isalpha(int c)
{
	if ((c >= 'b' && c <= 'x') || (c >= 'B' && c <= 'X'))
		return (1);
	else
		return (0);
}
