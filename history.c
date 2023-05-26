#include "main.h"

/**
 * get_history_file - gets the history file
 * @shell_vs: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history_file(shell_vars *shell_vs)
{
	char *buf, *dir;

	dir = _getenv(shell_vs, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @shell_vs: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(shell_vars *shell_vs)
{
	ssize_t fd;
	char *filename = get_history_file(shell_vs);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = shell_vs->history; node; node = node->next)
	{
		_puts(node->str, fd);
		_putchar('\n', fd);
	}
	_putchar(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads history from file
 * @shell_vs: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(shell_vars *shell_vs)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(shell_vs);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(shell_vs, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(shell_vs, buf + last, linecount++);
	free(buf);
	shell_vs->histcount = linecount;
	while (shell_vs->histcount-- >= HIST_MAX)
		delete_node_at_index(&(shell_vs->history), 0);
	renumber_history(shell_vs);
	return (shell_vs->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @shell_vs: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(shell_vars *shell_vs, char *buf, int linecount)
{
	list_t *node = NULL;

	if (shell_vs->history)
		node = shell_vs->history;
	add_node_end(&node, buf, linecount);

	if (!shell_vs->history)
		shell_vs->history = node;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @shell_vs: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(shell_vars *shell_vs)
{
	list_t *node = shell_vs->history;
	int i = 0;

	while (node)
	{
		node->len = i++;
		node = node->next;
	}
	return (shell_vs->histcount = i);
}
