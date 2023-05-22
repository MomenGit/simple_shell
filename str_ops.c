#include "main.h"

/**
 * num_of_substr - counts the number of substrings according to a delimiter
 *
 * @str: string to be operated on
 * @delimiter: the delimiter inside the string
 *
 * Return: number of substrings or 0 on error
 */
int num_of_substr(char *str, char delimiter)
{
	int num;

	if (str == NULL)
		return (0);

	num = 0;
	while (*str != '\0')
	{
		if (*str == delimiter)
			num++;
		str++;
	}

	return (num);
}

/**
 * str_split - splits a string according to a delimiter
 *
 * @str: string to be splitted
 * @delimiter: the delimiter used to split the string
 * Return: substring of string
 */
char *str_split(char *str, char delimiter)
{
	static char *next_substr;
	char *substr;

	if (str == NULL)
		str = next_substr;

	if (str == NULL || *str == '\0')
	{
		return NULL;
	}

	substr = str;

	while (*str != '\0')
	{
		if (*str == delimiter)
		{
			*str = '\0';
			next_substr = str + 1;
			return substr;
		}
		str++;
	}

	next_substr = NULL;
	return (substr);
}

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
