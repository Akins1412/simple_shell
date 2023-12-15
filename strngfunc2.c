#include "shell.h"
/**
 * duplicate_string - Creates a duplicate of the
 * provided string in a new memory
 * @str_to_duplicate: String to be duplicated
 *
 * Return: Pointer to the new duplicated string
 */
char *duplicate_string(char *str_to_duplicate)
{
	char *ct;

	int l, i;

	if (str_to_duplicate == 0)
		return (NULL);

	for (l = 0; str_to_duplicate[l]; l++)
		;
	ct = malloc((l + 1) * sizeof(char));

	for (i = 0; i <= l; i++)
		ct[i] = str_to_duplicate[i];

	return (ct);
}

/**
 * compare_strings - Compares the lengths of two strings
 * @str1: First string to be compared in length
 * @str2: Second string to be compared
 *
 * Return: 0 on success, any other value indicates a failure
 */
int compare_strings(char *str1, char *str2)
{
	int i;

	i = 0;
	while (str1[i] == str2[i])
	{
		if (str1[i] == '\0')
			return (0);
		i++;
	}
	return (str1[i] - str2[i]);
}
