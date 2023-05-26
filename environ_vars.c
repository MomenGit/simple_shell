#include "main.h"

/**
 * _env - prints the current environment
 * @shell_vs: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _env(shell_vars *shell_vs)
{
	print_list_str(shell_vs->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @shell_vs: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(shell_vars *shell_vs, const char *name)
{
	list_t *node = shell_vs->env;
	char *p;

	while (node)
	{
		p = _strstr(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _set_env - Initialize a new environment variable,
 *             or modify an existing one
 * @shell_vs: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _set_env(shell_vars *shell_vs)
{
	if (shell_vs->argc != 3)
	{
		_puts("Incorrect number of arguments\n", STDERR_FILENO);
		return (1);
	}
	if (_setenv(shell_vs, shell_vs->argv[1], shell_vs->argv[2]))
		return (0);
	return (1);
}

/**
 * _unset_env - Remove an environment variable
 * @shell_vs: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _unset_env(shell_vars *shell_vs)
{
	int i;

	if (shell_vs->argc == 1)
	{
		_puts("Too few arguments.\n", STDERR_FILENO);
		return (1);
	}
	for (i = 1; i <= shell_vs->argc; i++)
		_unsetenv(shell_vs, shell_vs->argv[i]);

	return (0);
}

/**
 * set_env_list - populates env linked list
 * @shell_vs: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int set_env_list(shell_vars *shell_vs)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	shell_vs->env = node;
	return (0);
}
