#include "main.h"
#include <stdio.h>
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
	char **argv;
	int argc, i;

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

		argc = num_of_substr(buffer, ' ');
		argc += 2;

		argv = malloc(sizeof(char *) * argc);
		argv[0] = str_split(buffer, ' ');

		for (i = 0; argv[i] != NULL; i++)
		{
			argv[i + 1] = str_split(NULL, ' ');
		}

		exec_child_proc(argv);
		free(argv);
	}

	return (0);
}
