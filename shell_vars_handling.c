#include "main.h"

/**
 * clear_vars - initializes shell_t struct
 * @shell_vs: struct address
 */
void clear_vars(shell_vars *shell_vs)
{
	shell_vs->arg = NULL;
	shell_vs->argv = NULL;
	shell_vs->path = NULL;
	shell_vs->argc = 0;
}

/**
 * set_vars - initializes shell_t struct
 * @shell_vs: struct address
 * @av: argument vector
 */
void set_vars(shell_vars *shell_vs, char **av)
{
	int i = 0;

	shell_vs->fname = av[0];
	if (shell_vs->arg)
	{
		shell_vs->argv = str_split(shell_vs->arg, " \t");
		if (!shell_vs->argv)
		{
			shell_vs->argv = malloc(sizeof(char *) * 2);
			if (shell_vs->argv)
			{
				shell_vs->argv[0] = _strdup(shell_vs->arg);
				shell_vs->argv[1] = NULL;
			}
		}
		for (i = 0; shell_vs->argv && shell_vs->argv[i]; i++)
			;
		shell_vs->argc = i;

		replace_alias(shell_vs);
		replace_vars(shell_vs);
	}
}

/**
 * free_vars - frees shell_t struct fields
 * @shell_vs: struct address
 * @all: true if freeing all fields
 */
void free_vars(shell_vars *shell_vs, int all)
{
	ffree(shell_vs->argv);
	shell_vs->argv = NULL;
	shell_vs->path = NULL;
	if (all)
	{
		if (!shell_vs->cmd_buf)
			free(shell_vs->arg);
		if (shell_vs->env)
			free_list(&(shell_vs->env));
		if (shell_vs->history)
			free_list(&(shell_vs->history));
		if (shell_vs->alias)
			free_list(&(shell_vs->alias));
		ffree(shell_vs->environ);
		shell_vs->environ = NULL;
		bfree((void **)shell_vs->cmd_buf);
		if (shell_vs->readfd > 2)
			close(shell_vs->readfd);
		_putchar(BUF_FLUSH, STDOUT_FILENO);
	}
}
