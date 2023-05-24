#include "main.h"

/**
 * main - program entry point
 *
 * @argc: arguments count
 * @argv: arguments passed to the program
 * Return: int
 */
int main(int argc, char *argv[])
{
	if (argc > 1)
	{
		argv++;
		if (!exec_built_in(argv))
			exec_child_proc(argv);
	}
	else
	{
		init_shell();
	}

	return (0);
}
