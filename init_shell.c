#include "main.h"
#include <stdio.h>
/**
 * init_shell - initializes the shell process
 *
 * Return: 0 on success, -1 on failure or error
 */
int init_shell(void)
{
	char *buffer, **argv;
	size_t len;
	ssize_t nread;

	while (1)
	{
		buffer = NULL;
		len = 0;
		write(1, "$ ", 2);

		nread = getline(&buffer, &len, stdin);

		if (nread == -1)
		{
			free(buffer);
			perror("Error: ");
			continue;
		}

		buffer[nread - 1] = '\0';

		argv = str_split(buffer, " \n");
		if (argv == NULL)
		{
			free(argv);
			free(buffer);
			continue;
		}

		if (!exec_built_in(argv))
			exec_child_proc(argv);

		free(argv);
		free(buffer);
	}
	free(argv);
	free(buffer);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	return (0);
}
