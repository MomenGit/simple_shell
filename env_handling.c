#include "main.h"

/**
 * get_environ - returns the string array copy of our environ
 * @shell_vs: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(shell_vars *shell_vs)
{
	if (!shell_vs->environ || shell_vs->env_changed)
	{
		shell_vs->environ = list_to_strings(shell_vs->env);
		shell_vs->env_changed = 0;
	}

	return (shell_vs->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @shell_vs: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(shell_vars *shell_vs, char *var)
{
	list_t *node = shell_vs->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = _strstr(node->str, var);
		if (p && *p == '=')
		{
			shell_vs->env_changed = delete_node_at_index(&(shell_vs->env), i);
			i = 0;
			node = shell_vs->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (shell_vs->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @shell_vs: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(shell_vars *shell_vs, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = shell_vs->env;
	while (node)
	{
		p = _strstr(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			shell_vs->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(shell_vs->env), buf, 0);
	free(buf);
	shell_vs->env_changed = 1;
	return (0);
}
