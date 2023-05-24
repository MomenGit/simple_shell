#include "main.h"
#include <sys/stat.h>

/**
 * search_env - searches env variables for a variable
 *
 * @keyword: the required keyword for searching
 * Return: char**
 */
char *search_env(char *keyword)
{
	int i, j;

	for (i = 0; __environ[i] != NULL; i++)
	{
		for (j = 0; keyword[j] != '\0' && __environ[i][j] == keyword[j]; j++)
			;
	};

	return (_strtok(&__environ[i][j], "\0"));
}

/**
 * path - returns the path variable
 *
 * Return: char**
 */
char **path(void)
{
	char path[] = "PATH=";
	int i, j;

	for (i = 0; __environ[i] != NULL; i++)
	{
		for (j = 0; j < 5 && __environ[i][j] == path[j]; j++)
			;
		if (j == 5)
			break;
	};

	return (str_split(&__environ[i][j], ":"));
}

/**
 * find_file - searches for a file
 *
 * Return: int
 */
int find_file(void)
{
	struct stat st;
	char **pathe;
	int i;
	int status;

	pathe = path();
	for (i = 0; pathe[i] != NULL; i++)
	{
		printf("%s:", pathe[i]);
		status = stat(pathe[i], &st);
		if (status == 0)
		{
			printf(" FOUND\n");
		}
		else
		{
			printf(" NOT FOUND\n");
		}
	}
	return (status);
}

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
		perror(argv[0]);
	}
	if (child_pid == 0)
	{
		if (execve(argv[0], argv, __environ) == -1)
		{
			perror(argv[0]);
		}
		sleep(2);
	}
	else
	{
		waitpid(child_pid, &status, 0);
	}

	return (0);
}
