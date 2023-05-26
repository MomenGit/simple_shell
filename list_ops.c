#include "lists.h"
#include "main.h"

/**
 * print_list_str - prints all the elements of a list_t list
 *
 * @h: the head of a list
 *
 * Return: the number of nodes
 */
size_t print_list_str(const list_t *h)
{
	size_t i;

	i = 0;
	while (h != NULL)
	{
		_puts(h->str ? h->str : "(nil)", STDOUT_FILENO);
		_putchar('\n', STDOUT_FILENO);

		i++;
		h = h->next;
	}

	return (i);
}

/**
 * list_len - number of elements in a linked list_t list
 *
 * @h: pointer to a list
 *
 * Return: length of the list
 */
size_t list_len(const list_t *h)
{
	size_t i;

	i = 0;
	while (h != NULL)
	{
		i++;
		h = h->next;
	}

	return (i);
}

/**
 * add_node - adds a new node at the beginning of a list_t list
 *
 * @head: the head of the list
 * @str: the new added string
 *
 * Return: the address of the new element, or NULL if it failed.
 */
list_t *add_node(list_t **head, const char *str)
{
	list_t *new;
	unsigned int i;

	new = malloc(sizeof(list_t));

	if (new == NULL)
	{
		free(new);
		return (NULL);
	}

	i = 0;
	if (str != NULL)
	{
		new->str = _strdup(str);
		while (new->str[i] != '\0')
			i++;
	}
	else
		new->str = NULL;

	new->len = i;
	new->next = *head;

	*head = new;

	return (*head);
}

/**
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->len = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * free_list - frees a list_t list
 *
 * @head: the head of the list
 * Return: Nothing
 */
void free_list(list_t **head)
{
	list_t *tmp;

	tmp = *head;
	while (tmp != NULL)
	{
		*head = (*head)->next;
		free(tmp->str);
		free(tmp);
		tmp = *head;
	}
}
