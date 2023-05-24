#include "main.h"

/**
 * print_env - prints the environment variable
 *
 */
void print_env(void)
{
	int i, j;

	for (i = 0; __environ[i] != NULL; i++)
	{
		for (j = 0; __environ[i][j] != '\0'; j++)
			write(1, &__environ[i][j], 1);
		write(1, "\n", 1);
	}
}

/**
 * print_working_dir - prints the path of the current working directory
 *
 */
void print_working_dir(void)
{
	int i;
	char *wd = getcwd(NULL, 0);

	for (i = 0; wd[i] != '\0'; i++)
		write(1, &wd[i], 1);
	write(1, "\n", 1);
	free(wd);
}

/**
 * exec_built_in - executes builtin commands
 *
 * @argv: arguments passed to the commands
 * Return: Always 0 or 1 to discontinue
 */
int exec_built_in(char *argv[])
{

	if (!_strcmp(argv[0], "exit"))
	{
		int status = 0;

		if (argv[1] != NULL)
			status = str_to_int(argv[1]);
		free(argv);
		exit(status);
	}
	else if (!_strcmp(argv[0], "env"))
	{
		print_env();
		return (1);
	}
	else if (!_strcmp(argv[0], "cd"))
	{
		if (chdir(argv[1]) == -1)
			perror("Error: ");
		return (1);
	}
	else if (!_strcmp(argv[0], "pwd"))
	{
		print_working_dir();
		return (1);
	}
	return (0);
}
