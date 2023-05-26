#include "main.h"

/**
 * interactive - returns  code to be true if shell is in interactive mode
 * @shell_vs: the structure address
 *
 * Return: if interactive in  mode return 1, 0 otherwise
 */
int interactive(shell_vars *shell_vs)
{
	return (isatty(STDIN_FILENO) && shell_vs->readfd <= 2);
}

/**
 * shell_init - main shell loop
 * @shell_vs: the parameter & return shell_vs struct
 * @argv: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int shell_init(shell_vars *shell_vs, char **argv)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_vars(shell_vs);
		if (interactive(shell_vs))
			_puts("$ ", STDOUT_FILENO);
		_putchar(BUF_FLUSH, STDERR_FILENO);
		r = get_input(shell_vs);
		if (r != -1)
		{
			set_vars(shell_vs, argv);
			builtin_ret = find_builtin(shell_vs);
			if (builtin_ret == -1)
				find_cmd(shell_vs);
		}
		else if (interactive(shell_vs))
			_putchar('\n', STDOUT_FILENO);
		free_vars(shell_vs, 0);
	}
	write_history(shell_vs);
	free_vars(shell_vs, 1);
	if (!interactive(shell_vs) && shell_vs->status)
		exit(shell_vs->status);
	if (builtin_ret == -2)
	{
		if (shell_vs->err_num == -1)
			exit(shell_vs->status);
		exit(shell_vs->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @shell_vs: the parameter & return shell_vs struct
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit()
 */
int find_builtin(shell_vars *shell_vs)
{
	int i, built_in_ret = -1;
	builtin_t builtin_tbl[] = {
		{"exit", _exiting},
		{"env", _env},
		{"setenv", _set_env},
		{"unsetenv", _unset_env},
		{"cd", _cd},
		{NULL, NULL}};

	for (i = 0; builtin_tbl[i].cmd; i++)
	{
		if (_strcmp(shell_vs->argv[0], builtin_tbl[i].cmd) == 0)
		{
			shell_vs->line_count++;
			built_in_ret = builtin_tbl[i].func(shell_vs);
			break;
		}
	}
	return (built_in_ret);
}
