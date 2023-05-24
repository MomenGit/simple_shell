#include "main.h"

/**
 * num_of_substr - counts the number of substrings according to a delimiter
 *
 * @str: string to be operated on
 * @delimiter: the delimiter inside the string
 *
 * Return: number of substrings or 0 on error
 */
int num_of_substr(char *str, char *delimiter)
{
	int num;
	char *d;

	if (str == NULL)
		return (0);

	num = 0;
	while (*str != '\0')
	{
		d = delimiter;
		while (*d != '\0')
		{
			if (*str == *d)
			{
				num++;
				break;
			}
			d++;
		}
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
char *_strtok(char *str, const char *delimiter)
{
	static char *next_substr;
	char *substr;

	if (str == NULL)
		str = next_substr;

	if (str == NULL || *str == '\0')
		return (NULL);

	substr = str;
	while (*str != '\0')
	{
		const char *d = delimiter;

		while (*d != '\0')
		{
			if (*d == *str)
			{
				*str = '\0';
				next_substr = str + 1;

				return (substr);
			}
			d++;
		}
		str++;
	}

	next_substr = NULL;
	return (substr);
}

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

	argc = num_of_substr(str, delimiter);
	argc += 1;

	splitted = malloc(sizeof(char *) * argc);
	splitted[0] = _strtok(str, delimiter);

	for (i = 0; splitted[i] != NULL; i++)
	{
		splitted[i + 1] = _strtok(NULL, delimiter);
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
 * @num: input number string
 *
 * Return: int from a string
 */
int str_to_int(char *num)
{
	int n, neg;

	n = 0;
	neg = 1;
	if (*num == '-')
	{
		neg = -1;
		num++;
	}
	while (*(num) != '\0')
	{
		n = n * 10 + (*num - '0');
		num++;
	}

	n *= neg;

	return (n);
}
