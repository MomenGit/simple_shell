#include "main.h"
#include <string.h>

/**
 * init_shell - initializes the shell process
 *
 * Return: 0 on success, -1 on failure or error
 */
int init_shell()
{
	char *buffer;
	size_t len;
	ssize_t nread;

	char *argv[] = {NULL, NULL};

	do
	{
		buffer = NULL;
		len = 0;
		write(1, "#super_simple_shell$ ", 22);
		nread = getline(&buffer, &len, stdin);

		if (nread == -1)
			return (-1);

		buffer[nread - 1] = '\0';
		if (!strcmp(buffer, "^C") || !strcmp(buffer, "exit"))
			break;

		argv[0] = buffer;

		exec_child_proc(argv);

	} while (1);

	return (0);
}
