#include <stdlib.h>
#include "lists.h"

/**
 * insert_dnodeint_at_index - inserts a new node at a given index
 * @h: pointer to the head of the list
 * @idx: index where the new node is added
 * @n: value of the new node
 *
 * Return: address of the new node, or NULL if it failed
 */
dlistint_t *insert_dnodeint_at_index(dlistint_t **h,
		unsigned int idx, int n)
{
	dlistint_t *new;
	dlistint_t *current;
	unsigned int i;

	if (h == NULL)
		return (NULL);

	if (idx == 0)
		return (add_dnodeint(h, n));

	current = *h;
	i = 0;

	while (current != NULL && i < idx)
	{
		current = current->next;
		i++;
	}

	if (current == NULL)
	{
		if (i == idx)
			return (add_dnodeint_end(h, n));

		return (NULL);
	}

	new = malloc(sizeof(dlistint_t));
	if (new == NULL)
		return (NULL);

	new->n = n;
	new->prev = current->prev;
	new->next = current;

	current->prev->next = new;
	current->prev = new;

	return (new);
}
