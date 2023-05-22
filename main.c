#include "main.h"

/**
 * main - program entry point
 *
 * @argc: arguments count
 * @argv: arguments passed to the program
 * Return: int
 */
int main(int argc, char *argv[], char **env)
{
	if (argv != NULL && argc != 0 && env != NULL)
		init_shell();
	return (0);
}
