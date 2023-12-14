#include "shell.h"

/**
 * custom_reallocate - doubles the size of a dynamically allocated array
 * @ptr: pointer to the old array
 * @size: pointer to the number of elements in the old array
 *
 * Returns: pointer to the newly allocated array
 */
char **custom_reallocate(char **ptr, size_t *size)
{
	char **new;
	size_t i;

	new = malloc(sizeof(char *) * ((*size) + 10));
	if (new == NULL)
	{
		free(ptr);
		return (NULL);
	}
	for (i = 0; i < (*size); i++)
	{
		new[i] = ptr[i];
	}
	*size += 10;
	free(ptr);
	return (new);
}
