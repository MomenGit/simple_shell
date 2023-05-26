#include "main.h"

/**
 * _strcpy - copies the string pointed to by src,
 * including the terminating null byte (\0), to the buffer pointed to by dest
 * @src: the string to be copied
 * @dest: the string to hold the copy
 *
 * Return: On success dest.
 * On error, .
 */
char *_strcpy(char *dest, char *src)
{
	int i;

	if (dest == src || *src == '\0')
		return (dest);
	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}

	dest[i] = '\0';
	return (dest);
}

/**
 * _strcat - concatenates two strings
 * @dest: the string to get appended
 * @src: the string to be appended to dest
 *
 * Return: On success the concatenated string.
 * On error, .
 */
char *_strcat(char *dest, char *src)
{
	char *str;

	str = dest;

	while (*str != '\0')
		str++;

	while (*src != '\0')
		*str++ = *src++;

	*str = '\0';
	return (dest);
}

/**
 * _strdup - returns a pointer to a newly allocated space in memory,
 * which contains a copy of the string given as a parameter
 * @str: string to be duplicated
 *
 * Return: On success pointer to duplicated string.
 * On error, NULL.
 */
char *_strdup(const char *str)
{
	int i;
	char *new_str;

	if (str == NULL)
		return (NULL);

	for (i = 0; str[i] != '\0'; i++)
		;

	new_str = malloc(sizeof(char) * (i + 1));

	if (new_str == NULL)
		return (NULL);

	for (i = 0; str[i] != '\0'; i++)
		new_str[i] = str[i];

	new_str[i] = str[i];
	return (new_str);
}

/**
 * _puts - prints an input string
 * @str: the string to be printed
 * @fd: file descriptor
 * Return: Nothing
 */
void _puts(char *str, int fd)
{
	int i = 0;

	if (fd < 1)
		fd = 1;
	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i], fd);
		i++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 * @fd: file descriptor
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;

	return (1);
}
