#include "main.h"

/**
 * _strcmp - compares two strings
 * @s1: first string of the comparison
 * @s2: second string of the comparison
 *
 * Return:
 * 0, if equal
 * -ve number, if s1 smaller than s2
 * +ve number, if s2 is greater than s2
 * On error, .
 */
int _strcmp(char *s1, char *s2)
{
	int res, i;

	res = 0;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			res = s1[i] - s2[i];
			break;
		}
		i++;
	}

	return (res);
}
