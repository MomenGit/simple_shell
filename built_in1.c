#include "main.h"

/**
 * _myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @shell_vs: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhistory(shell_vars *shell_vs)
{
	print_list(shell_vs->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @shell_vs: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(shell_vars *shell_vs, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(shell_vs->alias),
	get_node_index(shell_vs->alias, node_starts_with(shell_vs->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @shell_vs: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(shell_vars *shell_vs, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(shell_vs, str));

	unset_alias(shell_vs, str);
	return (add_node_end(&(shell_vs->alias), str, 0) == NULL, 0);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a, STDOUT_FILENO);
		_putchar('\'', STDOUT_FILENO);
		_puts(p + 1, STDOUT_FILENO);
		_puts("'\n", STDOUT_FILENO);
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @shell_vs: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(shell_vars *shell_vs)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (shell_vs->argc == 1)
	{
		node = shell_vs->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; shell_vs->argv[i]; i++)
	{
		p = _strchr(shell_vs->argv[i], '=');
		if (p)
			set_alias(shell_vs, shell_vs->argv[i]);
		else
			print_alias(node_starts_with(shell_vs->alias, shell_vs->argv[i], '='));
	}

	return (0);
}
