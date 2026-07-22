#include "dog.h"
#include <stdlib.h>

/**
 * _strlen - returns the length of a string
 * @s: string
 *
 * Return: length of string
 */
int _strlen(char *s)
{
	int i = 0;

	while (s[i])
		i++;

	return (i);
}

/**
 * _strcpy - copies a string
 * @dest: destination
 * @src: source
 *
 * Return: pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}

	dest[i] = '\0';

	return (dest);
}

/**
 * new_dog - creates a new dog
 * @name: dog's name
 * @age: dog's age
 * @owner: dog's owner
 *
 * Return: pointer to new dog, or NULL on failure
 */
dog_t *new_dog(char *name, float age, char *owner)
{
	dog_t *dog;
	char *new_name;
	char *new_owner;

	if (name == NULL || owner == NULL)
		return (NULL);

	dog = malloc(sizeof(dog_t));
	if (dog == NULL)
		return (NULL);

	new_name = malloc(sizeof(char) * (_strlen(name) + 1));
	if (new_name == NULL)
	{
		free(dog);
		return (NULL);
	}

	new_owner = malloc(sizeof(char) * (_strlen(owner) + 1));
	if (new_owner == NULL)
	{
		free(new_name);
		free(dog);
		return (NULL);
	}

	_strcpy(new_name, name);
	_strcpy(new_owner, owner);

	dog->name = new_name;
	dog->age = age;
	dog->owner = new_owner;

	return (dog);
}
