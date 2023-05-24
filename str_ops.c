#include "main.h"
#include <string.h>

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

	str++;

	return (num);
}

/**
 * _strtok - returns substr of a string according to a delimiter
 *
 * @str: ...
 * @delimiter: ...
 * Return: char*
 */
char *_strtok(char *str, const char *delimiter) {}

/**
 * str_split - splits a string
 *
 * @str:...
 * @delimiter: ...
 * Return: splitted string
 */
char **str_split(char *str, char *delimiter)
{
	char **splitted;
	int argc, i;

	argc = num_of_substr(str, ' ');
	argc += 1;

	splitted = malloc(sizeof(char *) * argc);
	splitted[0] = strtok(str, " \n");

	for (i = 0; splitted[i] != NULL; i++)
	{
		splitted[i + 1] = strtok(NULL, " ");
	}

	return (splitted);
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

/**
 * str_to_int - description
 * @n: input integer
 * @count: count of printed characters
 *
 * Return: count of digits printed.
 */
int str_to_int(int n, int count)
{
	count = 0;

	if (n < 0)
	{
		n = -n;
		count++;
	}
	if (n / 10)
	{
		count += str_to_int(n / 10, count);
	}
	/*_putchar(n % 10 + '0');*/
	count++;

	return (count);
}
