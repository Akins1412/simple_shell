#include "shell.h"

/**
 * custom_reallocate - doubles the size of a dynamically allocated array
 * @point: pointer to the old array
 * @size: pointer to the number of elements in the old array
 *
 * Returns: pointer to the newly allocated array
 */
char **custom_reallocate(char **point, size_t *size)
{
	char **rec;
	size_t i;

	rec = malloc(sizeof(char *) * ((*size) + 10));
	if (rec == NULL)
	{
		free(point);
		return (NULL);
	}
	for (i = 0; i < (*size); i++)
	{
		rec[i] = point[i];
	}
	*size += 10;
	free(point);
	return (rec);
}
