#ifndef LISTS_H
#define LISTS_H
#include <stdlib.h>
/**
 * struct list_s - singly linked list
 * @str: string - (malloc'ed string)
 * @len: length of the string
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */
typedef struct list_s
{
	char *str;
	unsigned int len;
	struct list_s *next;
} list_t;

size_t print_list_str(const list_t *h);
size_t print_list(const list_t *);
size_t list_len(const list_t *h);
list_t *add_node(list_t **head, const char *str);
list_t *add_node_end(list_t **head, const char *str, int num);
void free_list(list_t **head);
list_t *node__strstr(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);
int delete_node_at_index(list_t **, unsigned int);
char **list_to_strings(list_t *);
list_t *node_starts_with(list_t *node, char *prefix, char c);
#endif
