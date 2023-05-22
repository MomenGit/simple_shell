#include "main.h"

/**
 * init_shell - initializes the shell process
 *
 * Return: 0 on success, -1 on failure or error
 */
int init_shell(void)
{
	char *buffer;
	size_t len;
	ssize_t nread;

	char *argv[] = {NULL, NULL};

	while (1)
	{
		buffer = NULL;
		len = 0;
		write(1, "#super_simple_shell$ ", 22);
		nread = getline(&buffer, &len, stdin);

		if (nread == -1)
			return (-1);

		buffer[nread - 1] = '\0';
		if (!_strcmp(buffer, "^C") || !_strcmp(buffer, "exit"))
			break;

		argv[0] = buffer;

		exec_child_proc(argv);
	}

	return (0);
}
