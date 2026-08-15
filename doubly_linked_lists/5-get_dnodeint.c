#include "lists.h"

/**
 * get_dnodeint_at_index - gets a node at a given index
 * @head: pointer to the head of the list
 * @index: index of the node
 *
 * Return: pointer to the node, or NULL if it does not exist
 */
dlistint_t *get_dnodeint_at_index(dlistint_t *head, unsigned int index)
{
	unsigned int i = 0;

	while (head != NULL)
	{
		if (i == index)
			return (head);

		head = head->next;
		i++;
	}

	return (NULL);
}
