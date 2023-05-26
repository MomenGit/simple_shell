#include "main.h"

/**
 * _exiting - exits the shell
 * @shell_vs: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if shell_vs.argv[0] != "exit"
 */
int _exiting(shell_vars *shell_vs)
{
	int exit_check;

	if (shell_vs->argv[1]) /* If there is an exit argument */
	{
		exit_check = _atoi(shell_vs->argv[1]);
		if (exit_check == -1)
		{
			shell_vs->status = 2;
			print_error(shell_vs, "Illegal number: ");
			_puts(shell_vs->argv[1], STDERR_FILENO);
			_putchar('\n', STDERR_FILENO);
			return (1);
		}
		shell_vs->err_num = _atoi(shell_vs->argv[1]);
		return (-2);
	}
	shell_vs->err_num = -1;
	return (-2);
}

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
 * _cd - changes the current directory of the process
 * @shell_vs: Structure containing potential arguments.
 * Return: Always 0
 */
int _cd(shell_vars *shell_vs)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n", STDOUT_FILENO);
	if (!shell_vs->argv[1])
	{
		dir = _getenv(shell_vs, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _getenv(shell_vs, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(shell_vs->argv[1], "-") == 0)
	{
		if (!_getenv(shell_vs, "OLDPWD="))
		{
			_puts(s, STDOUT_FILENO);
			_putchar('\n', STDOUT_FILENO);
			return (1);
		}
		_puts(_getenv(shell_vs, "OLDPWD="), STDOUT_FILENO);
		_putchar('\n', STDOUT_FILENO);
		chdir_ret = chdir((dir = _getenv(shell_vs, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(shell_vs->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(shell_vs, "can't cd to ");
		_puts(shell_vs->argv[1], STDERR_FILENO), _putchar('\n', STDERR_FILENO);
	}
	else
	{
		_setenv(shell_vs, "OLDPWD", _getenv(shell_vs, "PWD="));
		_setenv(shell_vs, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _help - changes the current directory of the process
 * @shell_vs: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _help(shell_vars *shell_vs)
{
	char **arg_array;

	arg_array = shell_vs->argv;
	_puts("help call works. Function not yet implemented \n", STDOUT_FILENO);
	if (0)
		_puts(*arg_array, STDOUT_FILENO); /* temp att_unused workaround */
	return (0);
}
