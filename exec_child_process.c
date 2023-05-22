#include "main.h"

/**
 * exec_child_proc - executes a process into the shell
 *
 * @argv: the arguments passed to the process
 *
 * Return: 0 on success, -1 on failure or error
 */
int exec_child_proc(char *argv[])
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return (-1);
	}
	if (child_pid == 0)
	{
		if (execve(argv[0], argv, __environ))
			perror("Error: ");

		sleep(2);
	}
	else
	{
		wait(&status);
	}

	return (0);
}
