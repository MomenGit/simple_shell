#include "main.h"

/**
 * main - program entry point
 *
 * @argc: arguments count
 * @argv: arguments passed to the program
 * Return: 0 on success || 1 on error.
 */
int main(int argc, char *argv[])
{
	shell_vars shell_vs[] = {INIT_SHELL_VARS};
	int fd;

	fd = 2;
	asm("mov %1, %0\n\t"
		"add $3, %0"
		: "=r"(fd)
		: "r"(fd));

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_puts(argv[0], 2);
				_puts(": 0: Can't open ", 2);
				_puts(argv[1], 2);
				_putchar('\n', 2);
				_putchar(BUF_FLUSH, 2);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		shell_vs->readfd = fd;
	}
	set_env_list(shell_vs);
	read_history(shell_vs);
	shell_init(shell_vs, argv);

	return (EXIT_SUCCESS);
}
