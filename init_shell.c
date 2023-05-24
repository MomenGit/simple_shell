#include "main.h"

/**
 * read_line - reads line from user
 *
 * @buffer: the buffer used to read input
 * Return: buffer splitted into arguments
 */
char **read_line(char **buffer)
{
	size_t len;
	ssize_t nread;

	*buffer = NULL;
	len = 0;
	write(1, "$ ", 2);

	nread = getline(buffer, &len, stdin);

	if (nread == -1)
	{
		free(*buffer);
		perror("Error: ");
		return (NULL);
	}
	buffer[nread - 1] = '\0';

	return (str_split(*buffer, " \n"));
}

/**
 * init_shell - initializes the shell process
 *
 * Return: 0 on success, -1 on failure or error
 */
void init_shell(void)
{
	char **argv, *buffer;

	while (1)
	{
		argv = read_line(&buffer);
		if (argv == NULL)
		{
			free(argv);
			free(buffer);
			continue;
		}
		if (fflush(stdout) == EOF)
		{
			perror("");
			continue;
		}

		if (!exec_built_in(argv))
			exec_child_proc(argv);

		free(argv);
		free(buffer);
	}
	free(argv);
	free(buffer);
	exit(0);
}
