#include "main.h"

/**
 * _strncpy - copies n chars of string src to string dest
 * @dest: the destination of the copied string
 * @src: the copied string
 * @n: number of character to copied from src
 *
 * Return: On success dest.
 * On error, .
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[i] = src[i];

	for (; i < n; i++)
		dest[i] = '\0';

	return (dest);
}

/**
 * _strncat - concatenates two strings while using at most n bytes from src
 * @dest: the string to get appended
 * @src: the string to be appended to dest
 * @n: number of bytes
 *
 * Return: On success dest.
 * On error, .
 */
char *_strncat(char *dest, char *src, int n)
{
	int i;
	char *str;

	str = dest;

	while (*str != '\0')
		str++;

	for (i = 0; i < n && src[i] != '\0'; i++)
		*str++ = src[i];

	*str = '\0';
	return (dest);
}

/**
 * _strchr - a pointer to the first occurrence of the character c
 * in the string s, or NULL if the character is not found
 * @s: string to be operated on
 * @c: character to be found its first occurrence
 *
 * Return: On success pointer to first occurrence of c or NULL if !found.
 * On error, .
 */
char *_strchr(char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return (s);

		s++;
	}

	if (c == '\0')
		return (s);

	return (((void *)0));
}

/**
 * _strstr - locates a substring
 * @haystack: string to be searched for the substring needle
 * @needle: substring to be found in the string haystack
 *
 * Description:
 * finds the first occurrence of the substring needle in the string haystack.
 * The terminating null bytes (\0) are not compared
 *
 * Return: On success a pointer to the beginning of the located substring,
 * or NULL if the substring is not found.
 * On error, .
 */
char *_strstr(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strlen - returns the length of a string
 * @s: required string
 *
 * Return: On success string length.
 */
int _strlen(char *s)
{
	int len;

	len = 0;

	while (*(s + len) != '\0')
		len++;

	return (len);
}
